#include "../common/src/hive.hpp"
#include "../common/src/listener.hpp"
#include "palaceconnection.hpp"
#include "../id.hpp"
#include "../palaceserver.hpp"

PalaceConnection::PalaceConnection(HiveRef hive, ListenerPtr listener):
	Connection(hive),
	listener(listener)
{
}

void PalaceConnection::setSession(SessionRef session)
{
	this->session = session;
}

void PalaceConnection::onAccept(const std::string_view&, uint16)
{
	//PalaceConnectionPtr connection(new PalaceConnection(hive, listener));
	listener->accept(connection);

	PalaceOutStream tiyr;

	// Have the server send the user their ID upon connection
	int32 id = PalaceServer::getInstance()->getNextUserId();
	tiyr.write(Magic::tiyr);
	tiyr.write32(0);
	tiyr.write(id);
	connection->send(tiyr.data());

	PalaceServer::getInstance()->createSession(id, std::dynamic_pointer_cast<PalaceConnection>
		shared_from_this()));
}

void PalaceConnection::onSend(const ByteString&)
{
}

void PalaceConnection::onReceive(ByteString &data)
{
	PalaceInStream stream(data);
	uint32 event = stream.read();
	uint32 size = stream.read();
	int32 refNum = stream.read();

	sint32 userId = session->getId();
	PalaceServerRef inst = PalaceServer::getInstance();

	switch (event)
	{
		case Magic::regi:
		{
			// Copy the registration data for our reply back
			PalaceOutStream regi = buffer.clone(size);

			// Handle user and client details
			session->handleRegistration(ByteString);

			// Return the same packet as a logon reply and ref num set to the user ID
			Buffer rep2;
			rep2.write(Magic::rep2);
			rep2.write(size);
			rep2.write(userId);
			rep2.write(regi.getBytes());
			send(rep2.getBytes());

			// Also, send the server version
			Buffer vers;
			vers.write(Magic::vers);
			vers.write32(0);
			vers.write(Server::version);
			send(vers.getBytes());

			// And then the server info and user flags together (?)
			Buffer sinf_uSta;
			sinf_uSta.write(Magic::sinf);
			sinf_uSta.write32(8 + inst->getName().size());
			sinf_uSta.write(userId);
			sinf_uSta.write(inst->getPermissions());
			sinf_uSta.write<63>(inst->getName());
			sinf_uSta.write(inst->getOptions());
			sinf_uSta.write(Magic::uSta);
			sinf_uSta.write32(2);
			sinf_uSta.write(userId);
			sinf_uSta.write(session->getStatus());
			send(sinf_uSta.getBytes());

			// Finally, login event, content URL, room info, and room info end
			Buffer log_HTTP_room_endr;
			log_HTTP_room_endr.write(Magic::log);
			log_HTTP_room_endr.write32(4);
			log_HTTP_room_endr.write(userId);
			log_HTTP_room_endr.write(inst->getUserCount());
			log_HTTP_room_endr.write(Magic::HTTP);
			log_HTTP_room_endr.write32(inst->getContentUrl()->size());
			log_HTTP_room_endr.write(userId);
			log_HTTP_room_endr.writeCString(inst->getContentUrl());
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
