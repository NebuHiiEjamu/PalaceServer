#ifndef _LISTENER_H
#define _LISTENER_H

#include <atomic>
#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <string>

#include "forward.hpp"

using boost::asio;

class Listener : public std::enable_shared_from_this<Listener>
{
public:
	Listener(HivePtr);
	HivePtr getHive();
	asio::tcp::ip::acceptor& getAcceptor();
	asio::io_context::strand& getStrand();
	bool hasError();
	void listen(std::string_view, std::uint16_t);
	void accept(ConnectionPtr);
	void stop();
private:
	void dispatchAccept(ConnectionPtr);
	void handleAccept(asio::error_code, ConnectionPtr);
protected:
	virtual bool onAccept(ConnectionPtr, std::string_view, std::uint16_t);
	virtual void onError(asio::error_code);
protected:
	HivePtr hive;
	asio::tcp::ip::acceptor acceptor;
	asio::io_context::strand strand;
	std::atomic_uint32_t errorState;
};

#endif // _LISTENER_H
