//
//  Types.cpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#include "Types.hpp"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void printGameData(GameData gd)
{
    std::cout << "ships: " << gd.ships.size() << std::endl;
    for (size_t i = 0; i < gd.ships.size(); i++)
    {
        std::cout << "ship " << i << ": " << gd.ships[i].x << " " << gd.ships[i].y << " " << (int)gd.ships[i].unique_id << " " << (int)gd.ships[i].dir << " " << (int)gd.ships[i].powup << std::endl;
    }
    std::cout << "projectiles: " << gd.projectiles.size() << std::endl;
    for (size_t i = 0; i < gd.projectiles.size(); i++)
    {
        std::cout << "projectile " << i << ": " << gd.projectiles[i].x << " " << gd.projectiles[i].y << " " <<(int) gd.projectiles[i].unique_id << " " << (int)gd.projectiles[i].dir << std::endl;
    }
    std::cout << "powerups: " << gd.powerups.size() << std::endl;
    for (size_t i = 0; i < gd.powerups.size(); i++)
    {
        std::cout << "powerup " << i << ": " << gd.powerups[i].x << " " << gd.powerups[i].y << std::endl;
    }
    std::cout << "bombs: " << gd.bombs.size() << std::endl;
    for (size_t i = 0; i < gd.bombs.size(); i++)
    {
        std::cout << "bomb " << i << ": " << gd.bombs[i].x << " " << gd.bombs[i].y << std::endl;
    }
}
