//
//  Ship.cpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#include "Ship.hpp"

Ship::Ship() : Object(SHIP_HALFSIZE_IN_PIXELS) {}

Ship::~Ship() {}

Ship::Ship(uint8_t unique_id_) : Object(SHIP_HALFSIZE_IN_PIXELS)
{
    unique_id = unique_id_;
    dir = DEFAULT_START_DIRECTION;
    powup = false;
}

void Ship::move()
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
