#ifndef _SESSION_H
#define _SESSION_H

#include <array>
#include <bitset>
#include <cstdint>
#include <string>
#include <vector>

#include "forward.hpp"
#include "../forward.hpp"
#include "../net/forward.hpp"

enum class Client : std::uint8_t
{
	thePalace,
	palaceChat
};

enum class ClientPlatform : std::uint8_t
{
	unknown = 0,
	mac68k,
	macPPC,
	win16,
	win32,
	java
};

enum class Face : std::uint8_t
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
	Session(ServerRef);
	std::string&& getClientString() const;
	std::string&& getPlatformString() const;
private:
	PalaceConnectionPtr connection;
	ServerRef server;
	std::string userName;
	std::vector<std::uint8_t> password;
	std::array<AssetSpec, 9> props;
	std::bitset<UserStatus::all> status;
	Point position;
	std::int16_t room;
	Client client;
	ClientPlatform platform;
	Face face;
};

#endif // _SESSION_H
