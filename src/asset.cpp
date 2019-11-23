#include "asset.hpp"
#include "server.hpp"

static constexpr float propBit16 = 31 / 255;
static constexpr std::size_t pixelsS20 = 44 * 44;

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

/*ByteBuffer Asset::encodeS20Bit() const
{
}*/

void Asset::specToBuffer(ByteBuffer &buffer) const
{
	buffer.writeI32(id);
	buffer.writeU32(crc);
}

void Asset::descriptorToBuffer(ByteBuffer &buffer) const
{
	buffer.writeU32(status.to_ulong());
	buffer.writeU32(data.size());
	buffer.writeS31(name);
}
