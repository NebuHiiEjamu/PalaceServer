#include "room.hpp"

void State::toStream(PalaceOutStream &stream) const
{
}

void Spot::toStream(PalaceOutStream &stream) const
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

void Room::fullInfoToStream(PalaceOutStream &stream)
{
	static constexpr uint16 varStart = 40;

	LockGuard lock(mutex);
	PalaceOutStream proto;
	imageOffset,
		firstDrawOffset, firstPropOffset

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
	proto.pad(8); // offset (2) + reserved (2) + var length (2) + null offset (2)

	uint16 varStart = proto.getPosition();
	proto.writePString(name);
	uint16 backgroundOffset = proto.getPosition() - varStart;
	proto.writePString(background);
	uint16 artistOffset = proto.getPosition() - varStart;
	proto.writePString(artist);
	uint16 passwordOffset = proto.getPosition() - varStart;
	proto.writePString(password);

	for (const auto &[id, spot]: spotMap)
	{
		spot->pointsOffset = proto.getPosition() - varStart;
		for (const std::pair<int16, int16> &point : spot->points)
		{
			proto.write(point.first);
			proto.write(point.second);
		}
		spot->nameOffset = proto.getPosition() - varStart;
		proto.writePString(spot->name);
	}

	uint16 spotOffset = proto.getPosition() - varStart;
}

void Room::listInfoToStream(PalaceOutStream &stream) const
{
}
