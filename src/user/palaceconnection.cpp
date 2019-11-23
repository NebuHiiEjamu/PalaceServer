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
	buffer.readNull(8); // size and ref num not needed, todo: check if malformed?

	switch (event)
	{
		case idLogon:
		{
			// Process user and client details
			session->processRegistration(buffer);

			// Return the same packet as a logon reply and ref num set to the user ID
			PacketHeader replyHeader = header;
			replyHeader.event = idAltLogonReply;
			replyHeader.refCon = session->getId();

			std::ostringstream outStream;
			outStream.write(reinterpret_cast<const char*>(&replyHeader), sizeof(PacketHeader));
			outStream.write(reinterpret_cast<const char*>(&registration), sizeof(AuxRegistration));
			ByteBuffer reply(outStream.str().begin(), outStream.str().end());
			send(reply);
			outStream.str(std::string());

			// Also, send the server version
			PacketHeader versionHeader { idVersion, 0, Server::version };
			outStream.write(reinterpret_cast<const char*>(&versionHeader), sizeof(PacketHeader));
			ByteBuffer outVersion(outStream.str().begin(), outStream.str().end());
			send(outVersion);
			outStream.str(std::string());

			// And then the server info
			PacketHeader infoHeader { idServerInfo, sizeof(Packet_ServerInfo), session->getId() };
			Packet_ServerInfo serverInfo
			{
				Server::getInstance()->getPermissions(),
				Str63
				{
					Server::getInstance()->getName().size(),
					Server::getInstance()->getName().c_str()
				},
				Server::getInstance()->getOptions()
			};
			outStream.write(reinterpret_cast<const char*>(&infoHeader), sizeof(PacketHeader));
			outStream.write(reinterpret_cast<const char*>(&serverInfo), sizeof(Packet_ServerInfo));
			ByteBuffer outInfo(outStream.str().begin(), outStream.str().end());
			send(outInfo);
			outStream.str(std::string());

			// Followed by the user flags
			PacketHeader userFlagsHeader { idUserStatus, sizeof(uint16), session->getId() };
			uint16 userFlags = session->getStatus();
			outStream.write(reinterpret_cast<const char*>(&userFlagsHeader), sizeof(PacketHeader));
			outStream.write(reinterpret_cast<const char*>(&userFlags), sizeof(uint16));
			ByteBuffer outFlags(outStream.str().begin(), outStream.str().end());
			send(outFlags);
			break;
		}
		default:
			;
	}
}

void PalaceConnection::onError(asio::error_code)
{
}

void PalaceConnection::onDisconnect()
{
}
