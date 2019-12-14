#include "room.hpp"

void State::toStream(PalaceOutStream &stream) const
{
}

void Draw::toStream(PalaceOutStream &stream) const
{
}

void LooseProp::toStream(PalaceOutStream &stream) const
{
	stream.pad(8); // unused LLRec
	stream.write(id);
	stream.write(crc);
	stream.write32(attributes.to_ulong());
	stream.write(refCon);
	stream.write(y);
	stream.write(x);
}

void Room::fullInfoToStream(PalaceOutStream &stream) const
{
	static constexpr uint16 varStart = 40;

	LockGuard lock(mutex);
	PalaceOutStream proto;
	uint16 backgroundOffset, artistOffset, passwordOffset, spotOffset, imageOffset,
		firstDrawOffset, firstPropOffset, varStart;

	proto.write32(attributes.to_ulong());
	proto.write(faces);
	proto.write(id);
	proto.pad(8); // offsets to be filled in
	proto.write32(spotMap.size());
	proto.pad(2); // offset
	proto.write32(images.size());
	proto.pad(2); // offset
	proto.write32(draws.size());
	proto.pad(2); // offset
	proto.write32(users.size());
	proto.write32(looseProps.size());
	proto.pad(6); // offset (2) + reserved (2) + var length (2)

	proto.writePString(name);
	backgroundOffset = proto.getPosition() - varStart;
	proto.writePString(background);
	artistOffset = proto.getPosition() - varStart;
	proto.writePString(artist);
	passwordOffset = proto.getPosition() - varStart;
	proto.writePString(password);
	spotOffset = proto.getPosition() - varStart;
}

void Room::listInfoToStream(PalaceOutStream &stream) const
{
}
