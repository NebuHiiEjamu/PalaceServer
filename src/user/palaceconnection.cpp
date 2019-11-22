#include <iterator>
#include <sstream>

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

void PalaceConnection::onAccept(std::string_view, std::uint16_t)
{
	PalaceConnectionPtr connection(new PalaceConnection(hive, listener));
	listener->accept(connection);

	std::int32_t id = Server::getInstance()->getNextUserId();
	PacketHeader tiyid { idThisIsYourId, 0, id };
	std::ostringstream stream;

	stream.write(reinterpret_cast<const char*>(&tiyid), sizeof(PacketHeader));
	std::vector<std::uint8_t> out(stream.str().begin(), stream.str().end());
	connection->send(out);

	Server::getInstance()->createSession(id, std::dynamic_pointer_cast<PalaceConnection>
		shared_from_this()));
}

void PalaceConnection::onSend(const std::vector<std::uint8_t>&)
{
}

void PalaceConnection::onReceive(const std::vector<std::uint8_t> &buffer)
{
	std::istringstream inStream(std::string(buffer.begin(), buffer.end()));
	PacketHeader header;

	inStream.read(reinterpret_cast<char*>(&header), sizeof(PacketHeader));
	switch (header.event)
	{
		case idLogon:
		{
			AuxRegistration registration;
			stream.read(reinterpret_cast<char*>(&registration), sizeof(AuxRegistration));
			session->processRegistration(registration);

			PacketHeader replyHeader = header;
			replyHeader.event = idAltLogonReply;
			replyHeader.refCon = session->getId();

			std::ostringstream outStream;
			outStream.write(reinterpret_cast<const char*>(&replyHeader), sizeof(PacketHeader));
			outStream.write(reinterpret_cast<const char*>(&registration), sizeof(AuxRegistration));
			std::vector<std::uint8_t> reply(outStream.str().begin(), outStream.str().end());
			send(reply);
			outStream.str(std::string());

			PacketHeader versionHeader { idVersion, 0, Server::version };
			outStream.write(reinterpret_cast<const char*>(&versionHeader), sizeof(PacketHeader));
			std::vector<std::uint8_t> outVersion(outStream.str().begin(), outStream.str().end());
			send(outVersion);
			outStream.str(std::string());

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
			std::vector<std::uint8_t> outInfo(outStream.str().begin(), outStream.str().end());
			send(outInfo);
			outStream.str(std::string());

			PacketHeader userFlagsHeader { idUserStatus, sizeof(std::uint16_t), session->getId() };
			std::uint16_t userFlags = session->getStatus();
			outStream.write(reinterpret_cast<const char*>(&userFlagsHeader), sizeof(PacketHeader));
			outStream.write(reinterpret_cast<const char*>(&userFlags), sizeof(std::uint16_t));
			std::vector<std::uint8_t> outFlags(outStream.str().begin(), outStream.str().end());
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
