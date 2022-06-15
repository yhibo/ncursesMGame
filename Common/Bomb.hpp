//
//  Bomb.hpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 24/05/2022.
//

#ifndef Bomb_hpp
#define Bomb_hpp

#include "Object.hpp"

class Bomb : public Object {
public:
    Bomb();
    Bomb(int16_t x_, int16_t y_);
};

#endif /* Bomb_hpp */
