#include <cstring>
#include <iterator>

#include "session.hpp"
#include "palaceconnection.hpp"
#include "../net/packet.hpp"

Session::Session(const AuxRegistration &registration)
{
	userName = registration.userName.characters;
	password = std::vector<std::uint8_t>(std::begin(registration.password.characters),
		std::end(registration.password.characters + 31));
	
	switch (registration.flags & 0xF)
	{
		case 1: platform = ClientPlatform::mac68k; break;
		case 2: platform = ClientPlatform::macPPC; break;
		case 3: platform = ClientPlatform::win16; break;
		case 4: platform = ClientPlatform::win32; break;
		case 5: platform = ClientPlatform::java; break;
		default: platform = ClientPlatform::unknown;
	}

	if (std::strncmp(registration.reserved, "OPNPAL", 6) == 0)
		client = Client::openPalace;
	else if (std::strncmp(registration.reserved, "PC", 2) == 0)
		client = Client::palaceChat;
	else if (std::strncmp(registration.reserved, "PAL", 3) == 0)
		client = Client::thePalace;
	else client = Client::unknown;
}

std::string_view Session::getClientString() const
{
	switch (client)
	{
		case Client::thePalace: return "ThePalace"; break;
		case Client::openPalace: return "OpenPalace"; break;
		case Client::palaceChat: return "PalaceChat"; break;
		default: return "unknown";
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
