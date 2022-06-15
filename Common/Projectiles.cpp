//
//  Projectiles.cpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 24/05/2022.
//

#include "Projectiles.hpp"

Projectile::Projectile() : Object(OBJECT_HALFSIZE_IN_PIXELS) {}

Projectile::Projectile(int16_t x_, int16_t y_, uint8_t unique_id_, uint8_t dir_) : Object(x_, y_, OBJECT_HALFSIZE_IN_PIXELS)
{
    unique_id = unique_id_;
    dir = dir_;
}

void Projectile::move()
{
    switch (dir) {
        case DIR_UP:
            y--;
            break;
        case DIR_DOWN:
            y++;
            break;
        case DIR_LEFT:
            x--;
            break;
        case DIR_RIGHT:
            x++;
            break;
        default:
            break;
    }
}
