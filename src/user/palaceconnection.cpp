#include "palaceconnection.hpp"
#include "../net/hive.hpp"
#include "../net/listener.hpp"
#include "../id.hpp"
#include "../server.hpp"

PalaceConnection::PalaceConnection(HivePtr hive, ListenerPtr listener):
	Connection(hive),
	listener(listener)
{
}

void PalaceConnection::setSession(SessionRef session)
{
	this->session = session;
}

void PalaceConnection::onAccept(std::string_view, uint16)
{
	PalaceConnectionPtr connection(new PalaceConnection(hive, listener));
	listener->accept(connection);

	ByteBuffer tiyr;

	// Have the server send the user their ID upon connection
	int32 id = Server::getInstance()->getNextUserId();
	tiyr.writeU32(Magic::tiyr);
	tiyr.writeU32(0);
	tiyr.writeI32(id);
	connection->send(tiyr.getBytes());

	Server::getInstance()->createSession(id, std::dynamic_pointer_cast<PalaceConnection>
		shared_from_this()));
}

void PalaceConnection::onSend(const ByteString&)
{
}

void PalaceConnection::onReceive(ByteString &inString)
{
	ByteBuffer buffer(inString);
	uint32 event = buffer.readU32();
	uint32 size = buffer.readU32();
	int32 refNum = buffer.readI32();

	uint32 userId = session->getId();
	ServerRef inst = Server::getInstance();

	switch (event)
	{
		case Magic::regi:
		{
			// Copy the registration data for our reply back
			ByteBuffer regi = buffer.clone(size);

			// Process user and client details
			session->processRegistration(buffer);

			// Return the same packet as a logon reply and ref num set to the user ID
			ByteBuffer rep2;
			rep2.writeU32(Magic::rep2);
			rep2.writeU32(size);
			rep2.writeI32(userId);
			rep2.write(regi.getBytes());
			send(rep2.getBytes());

			// Also, send the server version
			ByteBuffer vers;
			vers.writeU32(Magic::vers);
			vers.writeU32(0);
			vers.writeI32(Server::version);
			send(vers.getBytes());

			// And then the server info
			ByteBuffer sinf;
			sinf.writeU32(Magic::sinf);
			sinf.writeU32(8 + inst->getName().size());
			sinf.writeI32(userId);
			sinf.writeU32(inst->getPermissions());
			sinf.writeS63(inst->getName());
			sinf.writeU32(inst->getOptions());
			send(sinf.getBytes());

			// Followed by the user flags
			ByteBuffer uSta;
			uSta.writeU32(Magic::uSta);
			uSta.writeU32(2);
			uSta.writeI32(userId);
			uSta.writeU16(session->getStatus());
			send(uSta.getBytes());
			break;
		}
		default:
			;
	}
}

void PalaceConnection::onError(Error)
{
}

void PalaceConnection::onDisconnect()
{
}
