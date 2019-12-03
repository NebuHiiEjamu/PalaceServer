#include <cstring>

#include "session.hpp"
#include "palaceconnection.hpp"

Session::Session(sint32 id, PalaceConnectionPtr connection):
	connection(connection),
	id(id)
{
}

void Session::processRegistration(ByteBuffer &buffer)
{
	buffer.readNull(8); // serial number
	userName = buffer.readStr31(true);
	password = buffer.readStr31(true);
	uint32 flags = buffer.read();
	buffer.readNull(20); // pseudo serial number (8) + demo data (12)
	int16 desiredRoom = buffer.read();
	std::array<char, 6> reserved = buffer.read(6); // usually client identifier
	buffer.readNull(24); // req. protocol ver (4) + capabilities (20)
	
	switch (flags & 0xF)
	{
		case 1: platform = ClientPlatform::mac68k; break;
		case 2: platform = ClientPlatform::macPPC; break;
		case 3: platform = ClientPlatform::win16; break;
		case 4: platform = ClientPlatform::win32; break;
		case 5: platform = ClientPlatform::java; break;
		default: platform = ClientPlatform::unknown;
	}

	if (std::strncmp(reserved.data(), "PC4237", 6) == 0)
		client = Client::palaceChat;
	else if (std::strncmp(reserved.data(), "OPNPAL", 6) == 0)
		client = Client::openPalace;
	else if (std::strncmp(reserved.data(), "PX4016", 6) == 0)
		client = Client::phalanx;
	else if (std::strncmp(reserved.data(), "350211", 6) == 0)
		client = Client::thePalace;
	else if (std::strncmp(reserved.data(), "J2.0\0\0", 6) == 0)
		client = Client::instantPalace;
	else client = Client::unknown;
}

std::string_view Session::getClientString() const
{
	switch (client)
	{
		case Client::palaceChat: return "PalaceChat"; break;
		case Client::openPalace: return "OpenPalace"; break;
		case Client::phalanx: return "Phalanx"; break;
		case Client::thePalace: return "ThePalace"; break;
		case Client::instantPalace: return "InstantPalace"; break;
		default: return "unknown client";
	}
}

std::string_view Session::getPlatformString() const
{
	switch (platform)
	{
		case ClientPlatform::mac68k: return "68k Mac"; break;
		case ClientPlatform::macPPC: return "PPC Mac"; break;
		case ClientPlatform::win16: return "16Bit Windows"; break;
		case ClientPlatform::win32: return "32Bit Windows"; break;
		case ClientPlatform::java: return "Java"; break;
		default: return "Unknown";
	}
}

sint32 Session::getId() const
{
	return id;
}

uint16 Session::getStatus()
{
	LockGuard(mutex);
	return static_cast<uint16>(status.to_ulong());
}

void Session::setStatus(uint16 flags)
{
	LockGuard(mutex);
	status = std::bitset<UserStatus::all>(flags);
}
