#ifndef _ASSET_H
#define _ASSET_H

#include <bitset>
#include <cstdint>
#include <string>

#include "common.hpp"

namespace AssetStatus
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
	void specToBuffer(ByteBuffer&) const;
	void descriptorToBuffer(ByteBuffer&) const;
	void computeCrc(const ByteString&);
	//ByteBuffer encodeS20Bit() const;
protected:
	std::string name;
	ByteString data;
	std::bitset<AssetStatus::all> status;
	int32 id;
	uint32 crc;
	int32 refCon;
};

class Image : public std::enable_shared_from_this<Image>
{
public:
	void toBuffer(ByteBuffer&) const;
private:
	std::string name;
	uint16 alpha;
};

#endif // _ASSET_H
