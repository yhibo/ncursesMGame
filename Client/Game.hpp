//
//  Game.hpp
//  Client
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "ClientAPI.hpp"
#include "ClientLayout.hpp"
#include "../Common/SerDes.hpp"
#include "../Common/Types.hpp"
#include <csignal>
#include <thread>

class Game
{
private:
    bool idisassgined;
    ClientAPI capi;
    ClientLayout cl;
    GameData gd;
    uint8_t unique_id;
    char * name;
    bool running;
    std::string winnername;
    GameStatus handleDataFromServer();
    void readInputFromUser();
    void gameManager();
public:
    // start game
    ~Game();
    void start(char *, char *, char *);
};

#endif /* Game_hpp */
