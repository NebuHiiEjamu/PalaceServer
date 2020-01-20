#ifndef _PALACE_SERVER_H
#define _PALACE_SERVER_H

#include <bitset>
#include <map>
#include <mutex>
#include <random>

#include "user/forward.hpp"
#include "forward.hpp"
#include "common/src/server.hpp"
#include "common/src/typedefs.hpp"

struct sqlite3;

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

class PalaceServer final : public Server
{
public:
	static constexpr int32 version = 0x1000016;
	
	static constexpr ServerPlatform getPlatform();
	static constexpr std::string_view getPlatformString();
	static constexpr std::string_view getDefaultDatabase();
	static PalaceServerRef getInstance();
	static void encode(ByteString&);
	static void decode(ByteString&);

	~PalaceServer();
	bool createSession(int32, PalaceConnectionPtr);
	void removeSession(int32);
	int32 getNextUserId();
	uint32 getPermissions() const;
	uint32 getOptions() const;
	uint32 getUserCount();
	std::string_view& getName() const;
	std::string_view& getContentUrl() const;
	void run(int, char**) override;
private:
	PalaceServer();
private:
	static std::shared_ptr<PalaceServer> instance;

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
	std::map<int16, ImagePtr> imageMap;
	std::map<int16, RoomPtr> roomMap;
	sqlite3 *db;
	std::mutex mutex;
	sint32 nextUserId;
	sint32 nextAssetId;
	sint32 nextImageId;
	sint16 nextRoomId;
};

#endif // _PALACE_SERVER_H
