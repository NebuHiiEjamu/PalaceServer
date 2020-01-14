#ifndef _ASSET_H
#define _ASSET_H

#include <bitset>

#include "stream.hpp"

namespace AssetAttributes
{
	enum
	{
		head = 1,
		ghost,
		rare,
		animate,
		bounce,
		format20Bit,
		format8Bit,
		format32Bit,
		formatS20Bit,
		png,
		all
	};
}

class Asset : public std::enable_shared_from_this<Asset>
{
public:
	static constexpr uint32 legacyFlags = 0xFFC1;
	static constexpr uint32 nullCrc = 0xD9216290;

	Asset();
	void specToStream(PalaceOutStream&) const;
	void descriptorToStream(PalaceOutStream&) const;
	void computeCrc(const ByteString&);
protected:
	std::string name;
	ByteString data;
	std::bitset<AssetAttributes::all> attributes;
	int32 id;
	uint32 crc;
	int32 refCon;
};

class Image : public std::enable_shared_from_this<Image>
{
public:
	void toStream(PalaceOutStream&) const;
private:
	std::string name;
	uint16 alpha;
	uint16 nameOffset;
};

#endif // _ASSET_H
