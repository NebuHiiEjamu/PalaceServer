#ifndef _PALACECONNECTION_H
#define _PALACECONNECTION_H

#include "forward.hpp"
#include "../net/forward.hpp"
#include "../net/connection.hpp"

class PalaceConnection : public Connection
{
public:
	PalaceConnection(HivePtr, ListenerPtr);
	void setSession(SessionRef);
protected:
	void onAccept(std::string_view, std::uint16_t) override;
	void onSend(const std::vector<std::uint8_t>&) override;
	void onReceive(const std::vector<std::uint8_t>&) override;
	void onError(asio::error_code) override;
	void onDisconnect() override;
private:
	SessionRef session;
	ListenerPtr listener;
};

#endif // _PALACECONNECTION_H
