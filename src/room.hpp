#ifndef _ROOM_H
#define _ROOM_H

#include <bitset>
#include <map>
#include <set>

#include "common.hpp"
#include "forward.hpp"

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
public:
	void toBuffer(ByteBuffer&) const;
private:
	int16 image;
	int16 imageX;
	int16 imageY;
};

class Spot : public std::enable_shared_from_this<Spot>
{
public:
	void toBuffer(ByteBuffer&) const;
private:
	std::string name;
	std::string script;
	std::bitset<ScriptEvents::all> scriptEvents;
	std::vector<std::pair<int16, int16>> points;
	std::vector<State> states;
	uint32 attributes;
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

	void toBuffer(ByteBuffer&) const;
private:
	DrawCommand command;
	ByteString data;
};


class LooseProp : public Asset
{
public:
	void toBuffer(ByteBuffer&) const;
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
	void fullInfoToBuffer(ByteBuffer&) const;
	void listInfoToBuffer(ByteBuffer&) const;
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
