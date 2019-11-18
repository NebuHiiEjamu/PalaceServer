#ifndef _ASSET_H
#define _ASSET_H

#include <bitset>
#include <cstdint>
#include <string>
#include <vector>

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
	static constexpr std::uint32_t legacyFlags = 0xFFC1;
	static constexpr std::uint32_t nullCrc = 0xD9216290;

	Asset();
	template <class Container> void specToBuffer(Container&) const;
	template <class Container> void descriptorToBuffer(Container&) const;
private:
	template <class Container> void generateCrc(const Container&) const;
	//template <class Container> Container encodeS20Bit() const;
protected:
	std::string name;
	std::bitset<AssetStatus::all> status;
	std::uint32_t crc;
	std::vector<std::uint8_t> data;
	std::int32_t refCon;
};

class Image : public std::enable_shared_from_this<Image>
{
private:
	std::string name;
	std::uint16_t alpha;
};

#endif // _ASSET_H
