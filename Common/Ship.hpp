//
//  Ship.hpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#ifndef Ship_hpp
#define Ship_hpp

#include "Object.hpp"

class Ship : public Object {
public:
    uint8_t unique_id;
    uint8_t dir;
    bool shot = false;
    uint8_t powupcounter = 0;
    bool powup;
    ~Ship();
    Ship();
    Ship(uint8_t unique_id_);
    void move();
};

#endif /* Ship_hpp */
