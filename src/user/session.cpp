#include "session.hpp"
#include "palaceconnection.hpp"
#include "../net/packet.hpp"

std::string&& Session::getClientString() const
{
	switch (client)
	{
		case Client::thePalace: return "ThePalace"; break;
		case Client::palaceChat: return "PalaceChat"; break;
		default: return "unknown";
	}
}

std::string&& Session::getPlatformString() const
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
