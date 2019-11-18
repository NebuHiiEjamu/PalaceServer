#include "palaceconnection.hpp"
#include "../net/hive.hpp"
#include "../net/listener.hpp"
#include "../net/packet.hpp"

PalaceConnection::PalaceConnection(SessionRef owner, HivePtr hive, ListenerPtr listener):
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
	packetBuffer.insert(packetBuffer.end(), buffer.begin(), buffer.end());

	PacketHeader header
}

void PalaceConnection::onError(asio::error_code)
{
}

void PalaceConnection::onDisconnect()
{
}
