#include "palaceconnection.hpp"
#include "../net/hive.hpp"
#include "../net/listener.hpp"
#include "../net/packet.hpp"
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

	ByteBuffer tiyid;

	// Have the server send the user their ID upon connection
	int32 id = Server::getInstance()->getNextUserId();
	tiyid.writeU32(idThisIsYourId);
	tiyid.writeU32(0);
	tiyid.writeI32(id);
	connection->send(tiyid.getBytes());

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

	switch (event)
	{
		case idLogon:
		{
			// Copy the registration data for our reply back
			ByteBuffer regi = buffer.clone(size);

			// Process user and client details
			session->processRegistration(buffer);

			// Return the same packet as a logon reply and ref num set to the user ID
			ByteBuffer rep2;
			rep2.writeU32(idAltLogonReply);
			rep2.writeU32(size);
			rep2.writeI32(session->getId());
			rep2.write(regi.getBytes());
			send(rep2.getBytes());

			// Also, send the server version
			ByteBuffer vers;
			vers.writeU32(idVersion);
			vers.writeU32(0);
			vers.writeI32(Server::version);
			send(vers.getBytes());

			// And then the server info
			ByteBuffer sinf;
			sinf.writeU32(idServerInfo);
			sinf.writeU32(8 + Server::getInstance()->getName().size());
			sinf.writeI32(session->getId());
			sinf.writeU32(Server::getInstance()->getPermissions());
			sinf.writeS63(Server::getInstance()->getName());
			sinf.writeU32(Server::getInstance()->getOptions());
			send(sinf.getBytes());

			// Followed by the user flags
			ByteBuffer uSta;
			uSta.writeU32(idUserStatus);
			uSta.writeU32(2);
			uSta.writeI32(session->getId());
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
