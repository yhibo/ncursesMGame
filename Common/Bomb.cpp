//
//  Bomb.cpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 24/05/2022.
//

#include "Bomb.hpp"

Bomb::Bomb() : Object(OBJECT_HALFSIZE_IN_PIXELS) {}

Bomb::Bomb(int16_t x_, int16_t y_) : Object(x_, y_, OBJECT_HALFSIZE_IN_PIXELS){}

