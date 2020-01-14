#include "asset.hpp"
#include "palaceserver.hpp"

Asset::Asset():
	crc(nullCrc),
	refCon(0)
{
}

void Asset::computeCrc(const ByteString &bytes)
{
	crc = nullCrc;

	for (Byte i : bytes)
		crc = ((crc << 1) | ((crc & 0x80000000) ? 1 : 0)) ^ i;
}

void Asset::specToStream(PalaceOutStream &stream) const
{
	stream.write(id);
	stream.write(crc);
}

void Asset::descriptorToStream(PalaceOutStream &stream) const
{
	stream.write32(attributes.to_ulong());
	stream.write32(data.size());
	stream.write<31>(name);
}
