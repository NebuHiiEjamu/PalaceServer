project(pserver)

set(SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
	common/src/acceptor.cpp
	common/src/connection.cpp
	common/src/hive.cpp
	common/src/logger.cpp
	common/src/server.cpp
	common/src/stream.cpp
	user/palaceconnection.cpp
	user/session.cpp
	asset.cpp
	main.cpp
	palaceserver.cpp
	room.cpp
	stream.cpp
)

add_executable(pserver ${SOURCE_FILES})
target_link_libraries(pserver fmt::fmt SQLite3_LIBRARIES)
