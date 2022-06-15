cmake_minimum_required(VERSION 3.5.1)
project(MultiplayerGame VERSION 0.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

set(CLIENT_FILES
        src/Client/ClientAPI.cpp
        src/Client/ClientAPI.hpp
        src/Client/ClientLayout.cpp
        src/Client/ClientLayout.hpp
	src/Client/Game.cpp
        src/Client/Game.hpp
        src/Client/main.cpp
        src/Common/Bomb.cpp
	src/Common/Bomb.hpp
	src/Common/Object.cpp
	src/Common/Object.hpp
	src/Common/PowerUp.cpp
	src/Common/PowerUp.hpp
	src/Common/Projectiles.cpp
	src/Common/Projectiles.hpp
	src/Common/SerDes.cpp
	src/Common/SerDes.hpp
	src/Common/Ship.cpp
	src/Common/Ship.hpp
	src/Common/Types.cpp
	src/Common/Types.hpp)

set(SERVER_FILES
        src/Server/Client.cpp
        src/Server/Client.hpp
        src/Server/GameServer.cpp
        src/Server/GameServer.hpp
	src/Server/Server.cpp
        src/Server/Server.hpp
	src/Server/ServerAPI.cpp
        src/Server/ServerAPI.hpp
        src/Server/main.cpp
        src/Common/Bomb.cpp
	src/Common/Bomb.hpp
	src/Common/Object.cpp
	src/Common/Object.hpp
	src/Common/PowerUp.cpp
	src/Common/PowerUp.hpp
	src/Common/Projectiles.cpp
	src/Common/Projectiles.hpp
	src/Common/SerDes.cpp
	src/Common/SerDes.hpp
	src/Common/Ship.cpp
	src/Common/Ship.hpp
	src/Common/Types.cpp
	src/Common/Types.hpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(client ${CLIENT_FILES})
add_executable(server ${SERVER_FILES})

# Add ncurses library
find_package(Curses  REQUIRED)
find_package (Threads)
include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries( client ${CURSES_LIBRARIES})
target_link_libraries ( client ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries ( server ${CMAKE_THREAD_LIBS_INIT})