#include <array>
#include <boost/predef.h>

#include "server.hpp"
#include "user/session.hpp"

static const std::array<std::uint32_t, 512> generateLookUpTable()
{
	std::uint32_t key = 666666;
	std::uint32_t quotient, remainder, k;
	std::array<std::uint32_t, 512> result;

	for (std::uint32_t &i : result)
	{
		quotient = key / 127773;
		remainder = key / 127773;
		k = 16807 * remainder - 2836 * quotient;
		key = k > 0 ? k : 2147483647;
		i = static_cast<std::uint32_t>(static_cast<double>(key / 2147483647 * 256));
	}

	return result;
}

static const std::array<std::uint32_t, 512> lookUpTable = generateLookUpTable();
Server::instance = std::make_shared<Server>();

template <class Container> void Server::encode(Container &buffer)
{
	std::uint8_t lastChar = 0;
	std::uint32_t rc = 0;
	std::uint8_t b;

	if (buffer.size() > 254) buffer.resize(254);

	for (auto &i : buffer)
	{
		b = i;
		i = static_cast<std::uint8_t>(b ^ lookUpTable[rc++] ^ lastChar);
		lastChar = static_cast<std::uint8_t>(i ^ lookUpTable[rc++]);
	}
}

template <class Container> void Server::decode(Container &buffer)
{
	std::uint8_t lastChar = 0;
	std::uint32_t rc = 0;
	std::uint8_t b;

	for (auto &i : buffer)
	{
		b = i;
		i = static_cast<std::uint8_t>(b ^ lookUpTable[rc++] ^ lastChar);
		lastChar = static_cast<std::uint8_t>(b ^ lookUpTable[rc++]);
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
		DROP TABLE IF EXISTS `spots`;\
		CREATE TABLE `spots` (\
			`id` INTEGER PRIMARY KEY AUTOINCREMENT,\
			`name` TEXT,\
			`room` INTEGER NOT NULL,\
			`room_id` INTEGER NOT NULL,\
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
	nextUserId(1)
{
}

bool Server::createSession(const AuxRegistration &registration)
{
	std::lock_guard<std::mutex> lock(sessionMutex);
	SessionPtr newSession = std::make_shared<Session>(registration);
	sessionMap[nextUserId++] = newSession;

	return true;
}

void Server::removeSession(std::int32_t id)
{
	sessionMap.erase(id);
}

std::int32_t Server::findAssetIdByCrc(std::uint32_t crc) const
{
	auto it = assetMap.find(crc);
	return it != assetMap.end() ? it->first : 0;
}

ServerRef Server::getInstance()
{
	return instance;
}
