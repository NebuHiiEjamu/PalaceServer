#ifndef _SERVER_H
#define _SERVER_H

#include <bitset>
#include <map>
#include <mutex>
#include <random>
#include <sqlite3.h>

#include "net/forward.hpp"
#include "user/forward.hpp"
#include "forward.hpp"
#include "common.hpp"

enum class ServerPlatform : Byte
{
	macintosh = 0,
	windows9X,
	windowsNT,
	unix
};

enum class ServerDown : int32
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
		advertising,
		instantPalace,
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

namespace ExtendedInfo
{
	enum
	{
		avatarUrl = 0,
		serverVersion,
		serverType,
		serverFlags,
		userCount,
		serverName,
		imageUrl,
		all
	};
}

class Server final : public std::enable_shared_from_this<Server>
{
public:
	static constexpr int32 version = 0x1000016;
	
	static constexpr ServerPlatform getPlatform();
	static constexpr std::string_view getPlatformString();
	static constexpr std::string_view getDefaultDatabase();
	static ServerRef getInstance();
	static void encode(ByteString&);
	static void decode(ByteString&);

	~Server();
	bool createSession(int32, PalaceConnectionPtr);
	void removeSession(int32);
	int32 getNextUserId();
	uint32 getPermissions() const;
	uint32 getOptions() const;
	std::string_view getName() const;
	std::string_view getContentUrl() const;
private:
	Server();
private:
	static std::shared_ptr<Server> instance;

	std::string name;
	std::string contentUrl;
	std::random_device randomDevice;
	std::mt19937 randomEngine;
	std::bitset<Configuration::all> configuration;
	std::bitset<ExtendedInfo::all> extendedInfo;
	std::bitset<Permissions::all> permissions;
	std::bitset<Options::all> options;
	std::map<int32, SessionPtr> sessionMap;
	std::map<int32, AssetPtr> assetMap;
	std::map<int32, ImagePtr> imageMap;
	std::map<int16, RoomPtr> roomMap;
	sqlite3 *db;
	std::mutex mutex;
	int32 nextUserId;
};

#endif // _SERVER_H
