#ifndef _SERVER_H
#define _SERVER_H

#include <bitset>
#include <cstdint>
#include <map>
#include <mutex>
#include <sqlite3.h>
#include <string>

#include "net/forward.hpp"
#include "user/forward.hpp"
#include "forward.hpp"

enum class ServerPlatform : std::uint8_t
{
	macintosh = 0,
	windows9X,
	windowsNT,
	unix
};

enum class ServerDown : std::int32_t
{
	unknown = 0,
	loggedOff,
	communicationError,
	flood,
	killedByPlayer,
	serverDown,
	unresponsive,
	killedBySystemOperator,
	serverFull,
	invalidSerialNumber,
	duplicateUser,
	deathPenaltyActive,
	banished,
	banishKill,
	noGuests,
	demoExpired,
	verbose
};

namespace Configuration
{
	enum
	{
		directPlay = 0,
		closed,
		guestsAreMembers,
		instantPalace = 4,
		palacePresents,
		all
	};
}

namespace Permissions
{
	enum
	{
		allowGuests = 0,
		allowCyborgs,
		allowPainting,
		allowCustomProps,
		allowWizards,
		wizardsMayKill,
		wizardsMayAuthor,
		playersMayKill,
		cyborgsMayKill,
		deathPenalty,
		purgeInactiveProps,
		killFlooders,
		noSpoofing,
		memberCreatedRooms,
		all
	};
}

namespace Options
{
	enum
	{
		saveSessionKeys = 0,
		passwordSecurity,
		chatLog,
		noWhisper,
		allowDemoMembers,
		authenticate,
		poundProtect,
		sort,
		authTrackLogOff,
		javaSecure,
		all
	};
}

class Server final : public std::enable_shared_from_this<Server>
{
public:
	static constexpr std::uint32_t version = 0x1000016;
	
	static constexpr ServerPlatform getPlatform();
	static constexpr std::string_view getPlatformString();
	static constexpr std::string_view getDefaultDatabase();
	static ServerRef getInstance();
	template <class Container> static void encode(Container&);
	template <class Container> static void decode(Container&);

	~Server();
	bool createSession(const AuxRegistration&);
	void removeSession(std::int32_t);
	std::int32_t findAssetIdByCrc(std::uint32_t) const;
private:
	Server();
private:
	static std::shared_ptr<Server> instance;

	std::string name;
	std::bitset<Configuration::all> configuration;
	std::bitset<Permissions::all> permissions;
	std::bitset<Options::all> options;
	std::map<std::int32_t, SessionPtr> sessionMap;
	std::map<std::int32_t, AssetPtr> assetMap;
	std::map<std::int32_t, ImagePtr> imageMap;
	std::map<std::int16_t, RoomPtr> roomMap;
	sqlite3 *db;
	std::mutex assetMutex;
	std::mutex imageMutex;
	std::mutex roomMutex;
	std::mutex sessionMutex;
	std::mutex dbMutex;
	std::int32_t nextUserId;
};

#endif // _SERVER_H
