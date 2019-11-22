#ifndef _SESSION_H
#define _SESSION_H

#include <array>
#include <bitset>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

#include "forward.hpp"
#include "../forward.hpp"
#include "../net/forward.hpp"

enum class Client : std::uint8_t
{
	unknown,
	thePalace,
	instantPalace,
	openPalace,
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
	Session(std::int32_t, PalaceConnectionPtr);
	std::string_view getClientString() const;
	std::string_view getPlatformString() const;
	std::int32_t getId() const;
	std::uint16_t getStatus();
	void setStatus(std::uint16_t);
	void processRegistration(const AuxRegistration&);
private:
	PalaceConnectionPtr connection;
	std::string userName;
	std::vector<std::uint8_t> password;
	std::array<AssetRef, 9> props;
	std::mutex mutex;
	std::bitset<UserStatus::all> status;
	std::int32_t id;
	std::int16_t room;
	std::int16_t x;
	std::int16_t y;
	Client client;
	ClientPlatform platform;
	Face face;
};

#endif // _SESSION_H
