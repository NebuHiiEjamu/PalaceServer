#include <functional>

#include "connection.hpp"
#include "hive.hpp"

Connection::Connection(HivePtr hive):
	hive(hive),
	socket(hive->getIOContext()),
	strand(hive->getIOContext()),
	errorState(0)
{
}

HivePtr Connection::getHive()
{
	return hive;
}

asio::io_context::strand& Connection::getStrand()
{
	return strand;
}

asio::ip::tcp::socket& Connection::getSocket()
{
	return socket;
}

bool Connection::hasError()
{
	std::uint32_t v1 = 1;
	std::uint32_t v2 = 1;
	return errorState.compare_exchange_strong(v1, v2);
}

void Connection::disconnect()
{
	onDisconnect();
	socket.close();
}

void Connection::startError(asio::error_code error)
{
	std::uint32_t v1 = 1;
	std::uint32_t v2 = 0;

	if (!errorState.compare_exchange_strong(v1, v2))
	{
		asio::error_code errorCode;

		socket.shutdown(Socket::shutdown_both, errorCode);
		socket.close(errorCode);
		onError(error);
	}
}

void Connection::dispatchReceive(std::uint32_t totalBytes)
{
	pendingReceives.push(totalBytes);
	if (pendingReceives.empty()) startReceive(totalBytes);
}

void Connection::dispatchSend(const std::vector<std::uint8_t> &buffer)
{
	bool shouldStartSend = pendingSends.empty();
	pendingSends.push(buffer);
	if (shouldStartSend) startSend();
}

void Connection::startReceive(std::uint32_t totalBytes)
{
	if (totalBytes > 0)
	{
		inBuffer.resize(totalBytes);
		asio::async_read(socket, asio::buffer(inBuffer), asio::bind_executor(strand,
			std::bind(&Connection::handleReceive, shared_from_this(), std::placeholders::_1,
				std::placeholders::_2)));
	}
	else
	{
		inBuffer.resize(inBufferSize);
		asio::async_read_some(socket, asio::buffer(inBuffer), asio::bind_executor(strand,
			std::bind(&Connection::handleReceive, shared_from_this(), std::placeholders::_1,
				std::placeholders::_2)));
	}
}

void Connection::startSend()
{
	if (!pendingSends.empty())
		asio::async_write(socket, asio::buffer(pendingSends.front()), asio::bind_executor(strand,
			std::bind(&Connection::handleSend, shared_from_this(), std::placeholders::_1,
			pendingSends.begin())));
}

void Connection::handleReceive(asio::error_code error, std::uint32_t receivedBytes)
{
	if (error || hasError() || hive->stopped()) startError(error);
	else
	{
		inBuffer.resize(receivedBytes);
		onReceive(inBuffer);
		receive();
		pendingReceives.pop();
		if (!pendingReceives.empty()) startReceive(pendingReceives.front());
	}
}

void Connection::handleSend(asio::error_code error, std::vector<std::uint8_t> &message)
{
	if (error || hasError() || hive->stopped()) startError(error);
	else
	{
		onSend(message);
		pendingSends.pop();
		startSend();
	}
}

void Connection::receive(std::uint32_t totalBytes = 0)
{
	strand.post(std::bind(&Connection::dispatchReceive, shared_from_this(), totalBytes));
}

void Connection::send(const std::vector<std::uint8_t> &buffer)
{
	strand.post(std::bind(&Connection::dispatchSend, shared_from_this(), buffer));
}

std::uint32_t Connection::getInBufferSize() const
{
	return inBufferSize;
}

void Connection::setInBufferSize(std::uint32_t newSize)
{
	inBufferSize = newSize;
}

void Connection::onAccept(std::string_view, std::uint16_t)
{
}

void Connection::onConnect(std::string_view, std::uint16_t)
{
}

void Connection::onSend(const std::vector<std::uint8_t>&)
{
}

void Connection::onReceive(const std::vector<std::uint8_t>&)
{
}

void Connection::onError(asio::error_code)
{
}

void Connection::onDisconnect()
{
}
