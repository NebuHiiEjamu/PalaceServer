#ifndef _ROOM_H
#define _ROOM_H

#include <bitset>
#include <set>

#include "common.hpp"

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
	sint32 image;
	int16 imageX;
	int16 imageY;
};

class Spot : public std::enable_shared_from_this<Spot>
{
private:
	std::string name;
	std::string script;
	std::bitset<ScriptEvents::all> scriptEvents;
	std::vector<std::pair<int16, int16>> points;
	State state;
	int16 x;
	int16 y;
};

class LooseProp : public Asset
{
public:
	void toBuffer(ByteBuffer&) const;
private:
	int16 x;
	int16 y;
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
	ByteString password;
	std::vector<LooseProp> looseProps;
	std::vector<Spot> spots;
	std::bitset<RoomStatus::all> status;
	std::mutex mutex;
	std::set<int32> users;
	int32 faces;
	sint16 id;
};

#endif // _ROOM_H
