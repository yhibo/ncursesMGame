//
//  Types.hpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#ifndef Types_hpp
#define Types_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <thread>
#include "Ship.hpp"
#include "Projectiles.hpp"
#include "PowerUp.hpp"
#include "Bomb.hpp"
#include "../Settings/GameSettings.h"
#include "unistd.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include <mutex>
#include <condition_variable>
#include <cstring>
#include <strings.h>
#include <signal.h>

enum GameStatus : uint8_t {
    WINNER,
    LOSER,
    ERROR
};

enum Header : uint8_t {
    H_NAME = 192,
    H_CHANGEDIR = 224,
    H_ID = 240,
    H_DATA = 248,
    H_WINNER = 252,
    H_LOSER = 254,
    H_RESTART = 255
};

#define HEADER_BYTES 1
#define ID_BYTES 1
#define DIR_BYTES 1
#define SHIP_BYTES 7
#define PROJECTILE_BYTES 6
#define POWERUP_BYTES 4
#define BOMB_BYTES 4
#define INT_BYTES 4
#define SHORT_BYTES 2
#define NVECTORS 4

#define SHOOT_CODE 7


struct GameData {
    std::vector<Ship> ships;
    std::vector<Projectile> projectiles;
    std::vector<PowerUp> powerups;
    std::vector<Bomb> bombs;
};

void error(const char *msg);

void printGameData(GameData gd);


#endif /* Types_hpp */
