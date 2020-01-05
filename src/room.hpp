#ifndef _ROOM_H
#define _ROOM_H

#include <bitset>
#include <map>
#include <set>

#include "stream.hpp"
#include "forward.hpp"

namespace ScriptEvents
{
	enum
	{
		select = 0,
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
public:
	void toStream(PalaceOutStream&) const;
private:
	int16 image;
	int16 imageX;
	int16 imageY;
};

enum class SpotType : uint16
{
	normal = 0,
	door,
	shutableDoor,
	lockableDoor,
	bolt,
	navArea
};

namespace SpotAttributes
{
	enum
	{
		draggable = 0,
		dontMoveHere,
		invisible,
		showName,
		showFrame,
		shadow,
		fill,
		all
	};
}

class Spot : public std::enable_shared_from_this<Spot>
{
public:
private:
	std::string name;
	std::string script;
	std::bitset<ScriptEvents::all> scriptEvents;
	std::vector<std::pair<int16, int16>> points;
	std::vector<State> states;
	std::bitset<SpotAttributes::all> attributes;
	SpotType type;
	int16 id;
	int16 destination;
	int16 x;
	int16 y;
	bool locked;
};

enum class DrawCommand : uint16
{
	path = 0,
	shape,
	text,
	detonate,
	erase,
	ellipse
};

class Draw : public std::enable_shared_from_this<Draw>
{
public:
	static constexpr uint16 dataOffset = 10;

	void toStream(PalaceOutStream&) const;
private:
	DrawCommand command;
	ByteString data;
};


class LooseProp : public Asset
{
public:
	void toStream(PalaceOutStream&) const;
private:
	int16 x;
	int16 y;
};

namespace RoomAttributes
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
	void fullInfoToStream(PalaceOutStream&) const;
	void listInfoToStream(PalaceOutStream&) const;
private:
	std::string name;
	std::string artist;
	std::string background;
	ByteString password;
	std::vector<LooseProp> looseProps;
	std::map<int16, SpotPtr> spotMap;
	std::vector<Draw> draws;
	std::bitset<RoomAttributes::all> attributes;
	std::mutex mutex;
	std::set<int16> images;
	std::set<int32> users;
	int32 faces;
	int16 id;
};

#endif // _ROOM_H
