//
//  Object.hpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 24/05/2022.
//

#ifndef Object_hpp
#define Object_hpp

#include <cstdint>
#include "../Settings/GameSettings.h"
#include <stdio.h>
#include <cmath>

enum Directions : uint8_t {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    NUM_DIR
};

class Object {
    uint8_t halfsize;
public:
    int16_t x;
    int16_t y;
    ~Object();
    Object(uint8_t h = 0);
    Object(int16_t x_, int16_t y_, uint8_t h = 0);
    int16_t getX();
    int16_t getY();
    bool collidesWith(Object);
    bool collidesWithBorder();
    uint8_t getHalfsize();
};

#endif /* Object_hpp */
