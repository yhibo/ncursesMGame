//
//  Game.cpp
//  Client
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#include "Game.hpp"
#include <chrono>
#include <stdio.h>

extern WINDOW* window;

Game::~Game()
{
    endwin();
    std::cout<<winnername;
}

void Game::start(char *host, char *port, char *name_)
{
    idisassgined = false;
    running = true;
    name = name_;
    capi.init(host, port);
    capi.connectToServer();
    gameManager();
}

void Game::readInputFromUser()
{
    char character = 'w';
    char previousDirChar = 'w';
    halfdelay(HALF_DELAY_GET_CHAR_IN_TENTH_OF_A_SEC);
    
    while (true)
    {
        if(!running)
        {
            cbreak();
            return;
        }
        character = getch();
        if(character != previousDirChar)
        {
            switch (character)
            {
                case 'w':
                    if(capi.sendInputToServer(DIR_UP)) previousDirChar = character;
                    else running = false;
                    break;
                    
                case 'a':
                    if(capi.sendInputToServer(DIR_LEFT)) previousDirChar = character;
                    else running = false;
                    break;
                    
                case 's':
                    if(capi.sendInputToServer(DIR_DOWN)) previousDirChar = character;
                    else running = false;
                    break;
                    
                case 'd':
                    if(capi.sendInputToServer(DIR_RIGHT)) previousDirChar = character;
                    else running = false;
                    break;
                    
                case ' ':
                    if(!capi.sendInputToServer(SHOOT_CODE)) running = false;
                    break;
            }
        }
    }
    
}

GameStatus Game::handleDataFromServer()
{
    uint8_t h;
    signal(SIGWINCH, &ClientLayout::handleResize);

    while(true)
    {
        if(capi.readHeaderFromServer(h)<0)
            return ERROR;

        
        switch (h)
        {
            case H_WINNER:
                winnername = name;
                return WINNER;
                
            case H_LOSER:
                if(capi.readWinnerNameFromServer(winnername)<0)
                    return ERROR;
                return LOSER;
                
            case H_DATA:
                if(capi.readGameDataFromServer(gd)<0)
                    return ERROR;
                break;
                
            case H_ID:
                if (!idisassgined) {
                    if(capi.readIDFromServer(unique_id)<0)
                        return ERROR;
                    if(capi.sendNameToServer(name)<0)
                        return ERROR;
                    idisassgined = true;
                }
                break;
                
            default:
                return ERROR;
        }

        window = cl.drawGame(gd, unique_id);
        if(window == NULL){
            continue;
        }
        wrefresh(window);
    }

}

void Game::gameManager()
{
    std::thread th(&Game::readInputFromUser, this);
    
    uint8_t finalstatus = handleDataFromServer();

    cl.drawEndGame(finalstatus, winnername);
    
    running = false;
    th.join();
}
