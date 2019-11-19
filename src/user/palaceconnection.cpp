#include <iterator>
#include <sstream>

#include "palaceconnection.hpp"
#include "../net/hive.hpp"
#include "../net/listener.hpp"
#include "../net/packet.hpp"

PalaceConnection::PalaceConnection(HivePtr hive, ListenerPtr listener):
	Connection(hive),
	owner(owner),
	listener(listener)
{
}

void PalaceConnection::onAccept(std::string_view host, std::uint16_t port)
{
	PalaceConnectionPtr connection(new PalaceConnection(owner, hive, listener));
	listener->accept(connection);
}

void PalaceConnection::onSend(const std::vector<std::uint8_t>&)
{
}

void PalaceConnection::onReceive(const std::vector<std::uint8_t> &buffer)
{
	std::istringstream stream(std::string(buffer.begin(), buffer.end()));
	PacketHeader header;

	stream.read(reinterpret_cast<char*>(&header), sizeof(PacketHeader));
	switch (header.event)
	{
		case idLogon:
		{
			AuxRegistration registration;
			stream.read(reinterpret_cast<char*>(&registration), sizeof(AuxRegistration));
			Server::getInstance()->createSession(registration);
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
