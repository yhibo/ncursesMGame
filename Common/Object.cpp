//
//  Object.cpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 24/05/2022.
//

#include "Object.hpp"

Object::~Object(){}

Object::Object(uint8_t h) : halfsize(h){}

Object::Object(int16_t x_, int16_t y_, uint8_t h)
{
    x = x_;
    y = y_;
    halfsize = h;
}

int16_t Object::getX()
{
    return x;
}

int16_t Object::getY()
{
    return y;
}

bool Object::collidesWith(Object obj)
{
    return (  (  abs(x-obj.x) < ( obj.halfsize+halfsize+1 )    ) &&
              (  abs(y-obj.y) < ( obj.halfsize+halfsize+1 )    )   );
}

uint8_t Object::getHalfsize()
{
    return halfsize;
}

bool Object::collidesWithBorder()
{
    return ( (x<halfsize) || (y<halfsize) ||
             (x>MAP_WIDTH-1-halfsize) || (y>MAP_HEIGHT-1-halfsize));
}
