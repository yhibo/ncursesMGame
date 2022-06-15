//
//  Serializer.cpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#include "SerDes.hpp"


//
// SEREALIZE COMMON TYPES
//

uint8_t * SerDes::serializeInt(uint8_t * buffer, int value)
{
    buffer[0] = (uint8_t) value;
    buffer[1] = (uint8_t) (value >> 8);
    buffer[2] = (uint8_t) (value >> 16);
    buffer[3] = (uint8_t) (value >> 24);
    return buffer + 4;
}

uint8_t * SerDes::serializeShort(uint8_t * buffer, int16_t value)
{
    buffer[0] = (uint8_t) value;
    buffer[1] = (uint8_t) (value >> 8);
    return buffer + 2;
}

uint8_t * SerDes::serializeUint8(uint8_t * buffer, uint8_t value)
{
    buffer[0] = (uint8_t) value;
    return buffer + 1;
}

uint8_t * SerDes::serializeCharArray(uint8_t * buffer, char * value, int size)
{
    for (int i = 0; i < size; i++)
    {
        buffer[i] = value[i];
    }
    return buffer + size;
}

uint8_t * SerDes::serializeBool(uint8_t * buffer, bool value)
{
    buffer[0] = (uint8_t) value;
    return buffer + 1;
}


//
// DESEREALIZE COMMON TYPES
//

uint8_t * SerDes::deserializeInt(uint8_t * buffer, int &value)
{
    value = (int) buffer[0];
    value |= (int) buffer[1] << 8;
    value |= (int) buffer[2] << 16;
    value |= (int) buffer[3] << 24;
    return buffer + 4;
}

uint8_t * SerDes::deserializeShort(uint8_t * buffer, int16_t &value)
{
    value = (short) buffer[0];
    value |= (short) buffer[1] << 8;
    return buffer + 2;
}

uint8_t * SerDes::deserializeUint8(uint8_t * buffer, uint8_t &value)
{
    value = (uint8_t) buffer[0];
    return buffer + 1;
}

uint8_t * SerDes::deserializeBool(uint8_t * buffer, bool &value)
{
    value = (bool) buffer[0];
    return buffer + 1;
}

uint8_t * SerDes::deserializeCharArray(uint8_t * buffer, char * value, int size)
{
    for (int i = 0; i < size; i++)
    {
        value[i] = buffer[i];
    }
    return buffer + size;
}

//
// SEREALIZE CUSTOM TYPES
//

uint8_t * SerDes::serializeShipVectorToNetwork(uint8_t * buffer, std::vector<Ship> ships)
{
    uint8_t * ptr = buffer;
    for (size_t i = 0; i < ships.size(); i++)
    {
        ptr = serializeShort(ptr, htons(ships[i].x));
        ptr = serializeShort(ptr, htons(ships[i].y));
        ptr = serializeUint8(ptr, ships[i].unique_id);
        ptr = serializeUint8(ptr, ships[i].dir);
        ptr = serializeBool(ptr, ships[i].powup);
    }
    return ptr;
}

uint8_t * SerDes::serializeProjectileVectorToNetwork(uint8_t * buffer, std::vector<Projectile> projectiles)
{
    uint8_t * ptr = buffer;
    for (size_t i = 0; i < projectiles.size(); i++)
    {
        ptr = serializeShort(ptr, htons(projectiles[i].x));
        ptr = serializeShort(ptr, htons(projectiles[i].y));
        ptr = serializeUint8(ptr, projectiles[i].unique_id);
        ptr = serializeUint8(ptr, projectiles[i].dir);
    }
    return ptr;
}

uint8_t * SerDes::serializePowerUpVectorToNetwork(uint8_t * buffer, std::vector<PowerUp> powerups)
{
    uint8_t * ptr = buffer;
    for (size_t i = 0; i < powerups.size(); i++)
    {
        ptr = serializeShort(ptr, htons(powerups[i].x));
        ptr = serializeShort(ptr, htons(powerups[i].y));
    }
    return ptr;
}

uint8_t * SerDes::serializeBombVectorToNetwork(uint8_t * buffer, std::vector<Bomb> bombs)
{
    uint8_t * ptr = buffer;
    for (size_t i = 0; i < bombs.size(); i++)
    {
        ptr = serializeShort(ptr, htons(bombs[i].x));
        ptr = serializeShort(ptr, htons(bombs[i].y));
    }
    return ptr;
}


uint8_t * SerDes::serializeGameDataToNetwork(uint8_t * buffer, GameData gd)
{
    buffer = serializeShipVectorToNetwork(buffer, gd.ships);
    buffer = serializeProjectileVectorToNetwork(buffer, gd.projectiles);
    buffer = serializePowerUpVectorToNetwork(buffer, gd.powerups);
    buffer = serializeBombVectorToNetwork(buffer, gd.bombs);
    return buffer;
}

uint8_t * SerDes::deserializeShipVectorFromNetwork(uint8_t * buffer, int size, std::vector<Ship> &ships)
{
    int16_t aux;
    ships.resize(size);
    for (int i = 0; i < size; i++)
    {
        buffer = deserializeShort(buffer, aux);
        ships[i].x = ntohs(aux);
        buffer = deserializeShort(buffer, aux);
        ships[i].y = ntohs(aux);
        buffer = deserializeUint8(buffer, ships[i].unique_id);
        buffer = deserializeUint8(buffer, ships[i].dir);
        buffer = deserializeBool(buffer, ships[i].powup);
    }
    return buffer;
}

uint8_t * SerDes::deserializeProjectileVectorFromNetwork(uint8_t * buffer, int size, std::vector<Projectile> &projectiles)
{
    int16_t aux;
    projectiles.resize(size);
    for (int i = 0; i < size; i++)
    {
        buffer = deserializeShort(buffer, aux);
        projectiles[i].x = ntohs(aux);
        buffer = deserializeShort(buffer, aux);
        projectiles[i].y = ntohs(aux);
        buffer = deserializeUint8(buffer, projectiles[i].unique_id);
        buffer = deserializeUint8(buffer, projectiles[i].dir);
    }
    return buffer;
}

uint8_t * SerDes::deserializePowerUpVectorFromNetwork(uint8_t * buffer, int size, std::vector<PowerUp> &powerups)
{
    int16_t aux;
    powerups.resize(size);

    for (int i = 0; i < size; i++)
    {
        buffer = deserializeShort(buffer, aux);
        powerups[i].x = ntohs(aux);
        buffer = deserializeShort(buffer, aux);
        powerups[i].y = ntohs(aux);
    }
    return buffer;
}

uint8_t * SerDes::deserializeBombVectorFromNetwork(uint8_t * buffer, int size, std::vector<Bomb> &bombs)
{
    int16_t aux;
    bombs.resize(size);
    for (int i = 0; i < size; i++)
    {
        buffer = deserializeShort(buffer, aux);
        bombs[i].x = ntohs(aux);
        buffer = deserializeShort(buffer, aux);
        bombs[i].y = ntohs(aux);
    }
    return buffer;
}

uint8_t * SerDes::deserializeGameDataFromNetwork(uint8_t * buffer, int sizes[], GameData &gd)
{


    buffer = deserializeShipVectorFromNetwork(buffer, sizes[0], gd.ships);

    buffer = deserializeProjectileVectorFromNetwork(buffer, sizes[1], gd.projectiles);

    buffer = deserializePowerUpVectorFromNetwork(buffer, sizes[2], gd.powerups);

    buffer = deserializeBombVectorFromNetwork(buffer, sizes[3], gd.bombs);
    
    return buffer;
}


// generate dummy GameData
GameData SerDes::createGameData(int size)
{
    GameData gd;
    gd.ships.resize(size);
    gd.projectiles.resize(size);
    gd.powerups.resize(size);
    gd.bombs.resize(size);
    for (int i = 0; i < size; i++)
    {
        gd.ships[i].x = i;
        gd.ships[i].y = i;
        gd.ships[i].unique_id = i;
        gd.ships[i].dir = i;
        gd.ships[i].powup = false;
        gd.projectiles[i].x = i + size*SHIP_BYTES;
        gd.projectiles[i].y = i + size*SHIP_BYTES;
        gd.projectiles[i].unique_id = i + size*SHIP_BYTES;
        gd.projectiles[i].dir = i + size*SHIP_BYTES;
        gd.powerups[i].x = i + size*SHIP_BYTES + size*PROJECTILE_BYTES;
        gd.powerups[i].y = i + size*SHIP_BYTES + size*PROJECTILE_BYTES;
        gd.bombs[i].x = i + size*SHIP_BYTES + size*PROJECTILE_BYTES + size*POWERUP_BYTES;
        gd.bombs[i].y = i + size*SHIP_BYTES + size*PROJECTILE_BYTES + size*POWERUP_BYTES;
    }
    return gd;
}


