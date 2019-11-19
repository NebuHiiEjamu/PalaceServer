#include <iterator>
#include <sstream>

#include "room.hpp"
#include "server.hpp"
#include "net/packet.hpp"

template <class Container> void LooseProp::toBuffer(Container &buffer) const
{
	LoosePropRec rec
	{
		emptyLink,
		AssetSpec { Server::getInstance()->findAssetIdByCrc(crc), crc },
		status.to_ulong(),
		refCon,
		Point { x, y }
	};

	std::ostringstrem stream;
	stream.write(reinterpret_cast<const char*>(&rec), sizeof(LoosePropRec));
	buffer.insert(std::back_inserter(buffer), stream.str().begin(), stream.str().end());
}
