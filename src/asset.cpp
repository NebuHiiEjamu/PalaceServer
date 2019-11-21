#include <iterator>
#include <sstream>

#include "asset.hpp"
#include "server.hpp"
#include "net/packet.hpp"

static constexpr float propBit16 = 31 / 255;
static constexpr std::size_t pixelsS20 = 44 * 44;

Asset::Asset():
	crc(nullCrc),
	refCon(0)
{
}

template <class Container> void Asset::generateCrc(const Container &buffer) const
{
	crc = nullCrc;

	for (std::uint8_t i : buffer)
		crc = ((crc << 1) | ((crc & 0x80000000) ? 1 : 0)) ^ i;
}

/*template <class Container> Container Asset::encodeS20Bit() const
{
}*/

template <class Container> void Asset::specToBuffer(Container &buffer) const
{
	AssetSpec spec { id, crc };
	std::ostringstrem stream;
	stream.write(reinterpret_cast<const char*>(&spec), sizeof(AssetSpec));
	buffer.insert(std::back_inserter(buffer), stream.str().begin(), stream.str().end());
}

template <class Container> void Asset::descriptorToBuffer(Container &buffer) const
{
	AssetDescriptor descriptor
	{
		status.to_ulong(),
		data.size(),
		std::string_view(name, 31)
	};

	std::ostringstrem stream;
	stream.write(reinterpret_cast<const char*>(&descriptor), sizeof(AssetDescriptor));
	buffer.insert(std::back_inserter(buffer), stream.str().begin(), stream.str().end());
}
