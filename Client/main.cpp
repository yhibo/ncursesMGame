//
//  main.cpp
//  Client
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#include <stdio.h>
#include <iostream>
#include "Game.hpp"
#include "ClientAPI.hpp"

int main(int argc, char *argv[]) {
    // Check if port and hostname were passed.
    if (argc < 4) {
        std::cout<<"Not enough arguments passed. Port, host and name required\n";
        exit(0);
    }
    Game game;
    game.start(argv[1], argv[2], argv[3]);
    return 0;
}
