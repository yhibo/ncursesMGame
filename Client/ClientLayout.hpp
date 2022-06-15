//
//  ClientLayout.hpp
//  Client
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#ifndef ClientLayout_hpp
#define ClientLayout_hpp

#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <ncurses.h>
#include <stdlib.h>
#include <wctype.h>
#include <locale.h>
#include <unistd.h>
#include "../Common/Types.hpp"

#define MAIN_MENU_BORDER_CHARACTER '+'

#define WINNER_TEXT "You Won!"
#define LOSER_TEXT "You Lost! Winner is: "
#define ERROR_TEXT "ERROR!"

class ClientLayout
{
private:
    int initWindow();
    void setColors();
    void drawShip(int16_t, int16_t, uint8_t, WINDOW*);
    void drawProjectile(int16_t, int16_t, uint8_t, WINDOW*);
    void drawDeath(int16_t, int16_t, WINDOW*);
    void drawBomb(int16_t, int16_t, WINDOW*);
    void drawPowerUp(int16_t, int16_t, WINDOW*);
    void setColor(int);
    void drawBorders(WINDOW*,int, int ,int ,int);
    void displayTextInCentre(std::string);
    WINDOW * modalLayout(int);
public:
    ClientLayout();
    ~ClientLayout();
    void drawEndGame(uint8_t, std::string);
    static void handleResize(int);
    WINDOW * drawGame(GameData gd, uint8_t id);
    static void deleteWindow(WINDOW *);
};


#endif /* ClientLayout_hpp */
