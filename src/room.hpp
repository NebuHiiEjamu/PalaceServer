#ifndef _ROOM_H
#define _ROOM_H

#include <bitset>
#include <mutex>
#include <set>
#include <string>
#include <vector>

namespace ScriptEvents
{
	enum
	{
		select,
		lock,
		unlock,
		hide,
		show,
		startup,
		alarm,
		custom,
		inChat,
		propChange,
		enter,
		leave,
		outChat,
		signOn,
		signOff,
		macro0,
		macro1,
		macro2,
		macro3,
		macro4,
		macro5,
		macro6,
		macro7,
		macro8,
		macro9,
		all
	};
}

class State
{
private:
	std::int32_t image;
	std::int16_t imageX;
	std::int16_t imageY;
};

class Spot : public std::enable_shared_from_this<Spot>
{
private:
	std::string name;
	std::string script;
	std::bitset<ScriptEvents::all> scriptEvents;
	std::vector<std::pair<std::int16_t, std::int16_t>> points;
	State state;
	std::int16_t x;
	std::int16_t y;
};

class LooseProp : public Asset
{
public:
	template <class Container> void toBuffer(Container&) const;
private:
	std::int16_t x;
	std::int16_t y;
};

namespace RoomStatus
{
	enum
	{
		authorLocked = 0,
		privated,
		noPainting,
		closed,
		cyborgFree,
		hidden,
		noGuests,
		wizardsOnly,
		dropOff,
		noLooseProps,
		all
	};
}

class Room : public std::enable_shared_from_this<Room>
{
public:
private:
	std::string name;
	std::string artist;
	std::string background;
	std::vector<std::uint8_t> password;
	std::vector<LooseProp> looseProps;
	std::vector<Spot> spots;
	std::bitset<RoomStatus::all> status;
	std::mutex mutex;
	std::set<std::int32_t> users;
	std::int32_t faces;
	std::int16_t id;
};

#endif // _ROOM_H
