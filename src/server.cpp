#include <array>
#include <boost/predef.h>
#include <sqlite3.h>

#include "server.hpp"
#include "net/packet.hpp"
#include "user/palaceconnection.hpp"
#include "user/session.hpp"

using LookupTable = std::array<std::uint32, 512>;

static const LookupTable generateLookUpTable()
{
	uint32 key = 666666;
	uint32 quotient, remainder, k;
	LookupTable result;

	for (uint32 &i : result)
	{
		quotient = key / 127773;
		remainder = key / 127773;
		k = 16807 * remainder - 2836 * quotient;
		key = k > 0 ? k : 2147483647;
		i = static_cast<uint32>(static_cast<double>(key / 2147483647 * 256));
	}

	return result;
}

static const LookupTable lookUpTable = generateLookUpTable();
std::shared_ptr<Server> Server::instance = std::make_shared<Server>();

void Server::encode(ByteString &inString)
{
	Byte lastChar = 0;
	uint32 rc = 0;
	Byte b;

	if (inString.size() > 254) inString.resize(254);

	for (auto &i : inString)
	{
		b = i;
		i = static_cast<Byte>(b ^ lookUpTable[rc++] ^ lastChar);
		lastChar = static_cast<Byte>(i ^ lookUpTable[rc++]);
	}
}

void Server::decode(ByteString &inString)
{
	Byte lastChar = 0;
	uint32 rc = 0;
	Byte b;

	for (auto &i : buffer)
	{
		b = i;
		i = static_cast<Byte>(b ^ lookUpTable[rc++] ^ lastChar);
		lastChar = static_cast<Byte>(b ^ lookUpTable[rc++]);
	}
}

constexpr ServerPlatform Server::getPlatform()
{
#if BOOST_OS_MACOS
	return ServerPlatform::macintosh;
#elif BOOST_OS_WINDOWS
	return ServerPlatform::windowsNT; // Windows 9X is not supported
#else
	return ServerPlatform::unix;
#endif
}

constexpr std::string_view Server::getPlatformString()
{
#if BOOST_OS_MACOS // first, because Mac OS X may collide with Unix
	return "Macintosh";
#elif BOOST_OS_WINDOWS // same here, in case of building with MinGW (?)
	return "Windows";
#elif BOOST_OS_UNIX
	return "Unix";
#else
	return "Unknown";
#endif
}

constexpr std::string_view Server::getDefaultDatabase()
{
	return "DROP TABLE IF EXISTS `assets`;\
		CREATE TABLE `assets` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`name` VARCHAR(31),\
			`crc` INTEGER NOT NULL,\
			`flags` INTEGER NOT NULL,\
			`width` INTEGER NOT NULL,\
			`height` INTEGER NOT NULL,\
			`ref_con` INTEGER NOT NULL,\
			`data` BLOB NOT NULL\
		);\
		DROP TABLE IF EXISTS `draws`;\
		CREATE TABLE `draws` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`room` INTEGER NOT NULL,\
			`data` BLOB NOT NULL\
		);\
		DROP TABLE IF EXISTS `images`;\
		CREATE TABLE `images` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`name` TEXT NOT NULL,\
			`alpha` INTEGER NOT NULL\
		);\
		\
		DROP TABLE IF EXISTS `loose_props`;\
		CREATE TABLE `loose_props` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`asset` INTEGER NOT NULL,\
			`x` INTEGER NOT NULL,\
			`y` INTEGER NOT NULL\
		);\
		DROP TABLE IF EXISTS `points`;\
		CREATE TABLE `points` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`x` INTEGER NOT NULL,\
			`y` INTEGER NOT NULL\
		);\
		\
		DROP TABLE IF EXISTS `rooms`;\
		CREATE TABLE `rooms` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`name` TEXT NOT NULL,\
			`background` TEXT,\
			`artist` TEXT,\
			`password` BLOB,\
			`faces` INTEGER NOT NULL,\
			`flags` INTEGER NOT NULL,\
			`spots` TEXT,\
			`draws` TEXT,\
			`loose_props` TEXT\
		);\
		\
		DROP TABLE IF EXISTS `sessions`;\
		CREATE TABLE `sessions` (\
			`id` INTEGER PRIMARY KEY,\
			`address` TEXT NOT NULL,\
			`room` INTEGER NOT NULL,\
			`flags` INTEGER NOT NULL\
		);\
		\
		DROP TABLE IF EXISTS `spots`;\
		CREATE TABLE `spots` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`name` TEXT,\
			`room` INTEGER NOT NULL,\
			`local_room_id` INTEGER NOT NULL,\
			`destination` INTEGER NOT NULL,\
			`state` INTEGER NOT NULL,\
			`type` INTEGER NOT NULL,\
			`flags` INTEGER NOT NULL,\
			`event_flags` INTEGER NOT NULL,\
			`points` TEXT NOT NULL,\
			`x` INTEGER NOT NULL,\
			`y` INTEGER NOT NULL,\
			`script` BLOB\
		);\
		\
		\
		INSERT INTO `rooms` (id, name, background, flags)\
			VALUES (86, 'Gate', 'clouds.png', 256);";
}

Server::Server():
	randomEngine(std::mt19937(randomDevice())),
	nextUserId(1)
{
}

bool Server::createSession(int32 id, PalaceConnectionPtr connection)
{
	LockGuard lock(mutex);
	SessionPtr newSession = std::make_shared<Session>(id, connection);
	connection->setSession(newSession);
	sessionMap[id] = newSession;

	return true;
}

void Server::removeSession(int32 id)
{
	sessionMap.erase(id);
}

sint32 Server::getNextUserId()
{
	LockGuard lock(mutex);
	return nextUserId++;
}

uint32 Server::getUserCount()
{
	LockGuard lock(mutex);
	return sessionMap.size();
}

uint32 Server::getPermissions() const
{
	return permissions.to_ulong();
}

uint32 Server::getOptions() const
{
	return options.to_ulong();
}

std::string_view Server::getName() const
{
	return name;
}

std::string_view Server::getContentbUrl() const
{
	return contentUrl;
}

ServerRef Server::getInstance()
{
	return instance;
}
