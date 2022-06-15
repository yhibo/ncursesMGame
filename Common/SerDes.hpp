//
//  Serializer.hpp
//  Multiplayer-Game
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#ifndef SerDes_hpp
#define SerDes_hpp

#include <stdio.h>
#include "Types.hpp"

namespace SerDes {

uint8_t * serializeInt(uint8_t * buffer, int value);
uint8_t * deserializeInt(uint8_t * buffer, int &value);

uint8_t * serializeShort(uint8_t * buffer, int16_t value);
uint8_t * deserializeShort(uint8_t * buffer, int16_t &value);

uint8_t * serializeBool(uint8_t * buffer, bool value);
uint8_t * deserializeBool(uint8_t * buffer, bool &value);

uint8_t * serializeCharArray(uint8_t * buffer, char * values, int size);
uint8_t * deserializeCharArray(uint8_t * buffer, char * values, int size);

uint8_t * serializeUint8(uint8_t * buffer, uint8_t value);
uint8_t * deserializeUint8(uint8_t * buffer, uint8_t &value);

uint8_t * serializeShipVectorToNetwork(uint8_t * buffer, std::vector<Ship> ships);
uint8_t * serializeProjectileVectorToNetwork(uint8_t * buffer, std::vector<Projectile> projectiles);
uint8_t * serializePowerUpVectorToNetwork(uint8_t * buffer, std::vector<PowerUp> powerups);
uint8_t * serializeBombVectorToNetwork(uint8_t * buffer, std::vector<Bomb> bombs);
uint8_t * serializeGameDataToNetwork(uint8_t * buffer, GameData gameData);

uint8_t * deserializeShipVectorFromNetwork(uint8_t * buffer, int size, std::vector<Ship> &ships);
uint8_t * deserializeProjectileVectorFromNetwork(uint8_t * buffer, int size, std::vector<Projectile> &projectiles);
uint8_t * deserializePowerUpVectorFromNetwork(uint8_t * buffer, int size, std::vector<PowerUp> &powerups);
uint8_t * deserializeBombVectorFromNetwork(uint8_t * buffer, int size, std::vector<Bomb> &bombs);
uint8_t * deserializeGameDataFromNetwork(uint8_t * buffer,int sizes[], GameData &gameData);

GameData createGameData(int size);

};



#endif /* Serializer_hpp */
