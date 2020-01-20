#ifndef _PALACECONNECTION_H
#define _PALACECONNECTION_H

#include "forward.hpp"
#include "../common/src/connection.hpp"

class PalaceConnection : public Connection<boost::asio::ip::tcp>
{
public:
	void setSession(SessionRef);
protected:
	PalaceConnection(HiveRef, ListenerPtr);
	void onAccept(const std::string_view&, uint16) override;
	void onSend(const Buffer&) override;
	void onReceive(Buffer&) override;
	void onError(Error) override;
	void onDisconnect() override;
private:
	SessionRef session;
	ListenerPtr listener;
};

#endif // _PALACECONNECTION_H
