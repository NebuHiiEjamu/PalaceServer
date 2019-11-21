#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <atomic>
#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "forward.hpp"

using boost::asio;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
	HivePtr getHive();
	asio::io_context::strand& getStrand();
	asio::ip::tcp::socket& getSocket();
	std::uint32_t getInBufferSize() const;
	void setInBufferSize(std::uint32_t);
	bool hasError();
	void disconnect();
	void receive(std::uint32_t);
	void send(const std::vector<std::uint8_t>&);
private:
	void dispatchReceive(std::uint32_t);
	void dispatchSend(const std::vector<std::uint8_t>&);
	void startReceive(std::uint32_t);
	void startSend();
	void handleReceive(asio::error_code, std::uint32_t);
	void handleSend(asio::error_code, std::queue<std::vector<std::uint8_t>>);
	void startError(asio::error_code);
protected:
	Connection(HivePtr);
	virtual void onAccept(std::string_view, std::uint16_t);
	virtual void onConnect(std::string_view, std::uint16_t);
	virtual void onSend(const std::vector<std::uint8_t>&);
	virtual void onReceive(const std::vector<std::uint8_t>&);
	virtual void onError(asio::error_code);
	virtual void onDisconnect();
protected:
	HivePtr hive;
	asio::ip::tcp::socket socket;
	asio::io_context::strand strand;
	std::vector<std::uint8_t> inBuffer;
	std::atomic_uint32_t errorState;
	std::queue<std::uint32_t> pendingReceives;
	std::queue<std::vector<std::uint8_t>> pendingSends;
	std::uint32_t inBufferSize;
};

#endif // _CONNECTION_H
