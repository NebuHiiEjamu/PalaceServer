#include "room.hpp"

void State::toBuffer(ByteBuffer &buffer) const
{
}

void Draw::toBuffer(ByteBuffer &buffer) const
{
}

void LooseProp::toBuffer(ByteBuffer &buffer) const
{
	buffer.writeNull(8); // unused LLRec
	buffer.write(id);
	buffer.write(crc);
	buffer.write32(attributes.to_ulong());
	buffer.write(refCon);
	buffer.write(y);
	buffer.write(x);
}

void Room::fullInfoToBuffer(ByteBuffer &buffer) const
{
	static constexpr uint16 varStart = 40;

	LockGuard lock(mutex);
	ByteBuffer proto;
	uint16 backgroundOffset, artistOffset, passwordOffset, spotOffset, imageOffset,
		firstDrawOffset, firstPropOffset, varStart;

	proto.write32(attributes.to_ulong());
	proto.write(faces);
	proto.write(id);
	proto.writeNull(8); // offsets to be filled in
	proto.write32(spotMap.size());
	proto.writeNull(2); // offset
	proto.write32(images.size());
	proto.writeNull(2); // offset
	proto.write32(draws.size());
	proto.writeNull(2); // offset
	proto.write32(users.size());
	proto.write32(looseProps.size());
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
