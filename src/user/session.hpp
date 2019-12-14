#ifndef _SESSION_H
#define _SESSION_H

#include <array>
#include <bitset>

#include "forward.hpp"
#include "../forward.hpp"
#include "../common/src/typedefs.hpp"

enum class Client : Byte
{
	unknown,
	thePalace,
	instantPalace,
	phalanx,
	openPalace,
	palaceChat
};

enum class ClientPlatform : Byte
{
	unknown = 0,
	mac68k,
	macPPC,
	win16,
	win32,
	java
};

enum class Face : Byte
{
	closed,
	smile,
	tiltDown,
	talk,
	winkLeft,
	normal,
	winkRight,
	tiltLeft,
	tiltUp,
	tiltRight,
	sad,
	blotto,
	angry
};

namespace UserStatus
{
	enum
	{
		superUser = 0,
		god,
		killed,
		guest,
		banished,
		penalized,
		communicationError,
		gagged,
		pinned,
		hidden,
		rejectOutsideRoom,
		rejectInsideRoom,
		propGagged,
		all
	};
}

class Session : public std::enable_shared_from_this<Session>
{
public:
	Session(int32, PalaceConnectionPtr);
	std::string_view getClientString() const;
	std::string_view getPlatformString() const;
	sint32 getId() const;
	uint16 getStatus();
	void setStatus(uint16);
	void handleRegistration(Buffer&);
private:
	PalaceConnectionPtr connection;
	std::string userName;
	ByteString password;
	std::array<AssetRef, 9> props;
	std::mutex mutex;
	std::bitset<UserStatus::all> status;
	int32 id;
	int16 room;
	int16 x;
	int16 y;
	Client client;
	ClientPlatform platform;
	Face face;
};

#endif // _SESSION_H
