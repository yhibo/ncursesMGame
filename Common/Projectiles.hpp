//
//  Projectiles.hpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 24/05/2022.
//

#ifndef Projectiles_hpp
#define Projectiles_hpp

#include "Object.hpp"

class Projectile : public Object {
public:
    uint8_t unique_id;
    uint8_t dir;
    Projectile();
    Projectile(int16_t x_, int16_t y_, uint8_t unique_id_, uint8_t dir);
    void move();
};


#endif /* Projectiles_hpp */
