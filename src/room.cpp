#include "room.hpp"

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
