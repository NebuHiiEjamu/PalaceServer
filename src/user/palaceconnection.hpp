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
	void onAccept(std::string_view, uint16) override;
	void onSend(const ByteString&) override;
	void onReceive(ByteString&) override;
	void onError(Error) override;
	void onDisconnect() override;
private:
	SessionRef session;
	ListenerPtr listener;
};

#endif // _PALACECONNECTION_H
