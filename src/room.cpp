#include "room.hpp"

void State::toBuffer(ByteBuffer &buffer) const
{
}

void Spot::toBuffer(ByteBuffer &buffer) const
{
	buffer.writeU32(scriptEvents.to_ulong());
	buffer.writeU32(attributes);
	buffer.writeNull(8); // unused
	buffer.writeI16(y);
	buffer.writeI16(x);
}

void Draw::toBuffer(ByteBuffer &buffer) const
{
}

void LooseProp::toBuffer(ByteBuffer &buffer) const
{
	buffer.writeNull(8); // unused LLRec
	buffer.writeI32(id);
	buffer.writeU32(crc);
	buffer.writeU32(status.to_ulong());
	buffer.writeI32(refCon);
	buffer.writeI16(y);
	buffer.writeI16(x);
}

void Room::fullInfoToBuffer(ByteBuffer &buffer) const
{
	static constexpr uint16 varStart = 40;

	LockGuard lock(mutex);
	ByteBuffer proto;
	uint16 backgroundOffset, artistOffset, passwordOffset, spotOffset, imageOffset,
		firstDrawOffset, firstPropOffset, varStart;

	proto.writeU32(attributes.to_ulong());
	proto.writeI32(faces);
	proto.writeI16(id);
	proto.writeNull(8); // offsets to be filled in
	proto.writeU16(spotMap.size());
	proto.writeNull(2); // offset
	proto.writeU16(images.size());
	proto.writeNull(2); // offset
	proto.writeU16(draws.size());
	proto.writeNull(2); // offset
	proto.writeU16(users.size());
	proto.writeU16(looseProps.size());
	proto.writeNull(6); // offset (2) + reserved (2) + var length (2)

	proto.writePString(name);
	backgroundOffset = proto.getSize() - varStart;
	proto.writePString(background);
	artistOffset = proto.getSize() - varStart;
	proto.writePString(artist);
	passwordOffset = proto.getSize() - varStart;
	proto.writePString(password);
	spotOffset = proto.getSize() - varStart;
}

void Room::listInfoToBuffer(ByteBuffer &buffer) const
{
}
