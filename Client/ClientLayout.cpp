//
//  ClientLayout.cpp
//  Client
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#include "ClientLayout.hpp"

#define SHIP_COLORS 4

WINDOW * window = NULL;

//Initialize window and renderer
ClientLayout::ClientLayout(){
    initWindow();
}

ClientLayout::~ClientLayout(){
    deleteWindow(window);
    clear();
    endwin();
}

int ClientLayout::initWindow(){

    setlocale(LC_CTYPE, "");

    initscr();
    // Check if terminal has colours
    if (has_colors() == FALSE) {
        endwin();
        printf("Terminal does not support colors!!\n");
        exit(1);
    }
    // Start the colours
    start_color();
    setColors();
    // Set cursor to invisible
    curs_set(0);
    // Allows more control for the input
    cbreak();
    // Do not display inserted keys to the screen.
    noecho();

    return 0;
}

void ClientLayout::deleteWindow(WINDOW * window) {
    if (window == NULL) {
        return;
    }
    wclear(window);
    wrefresh(window);
    delwin(window);
}

void ClientLayout::setColors() {
    init_color(COLOR_BLACK, 150, 120, 120);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_color(COLOR_RED, 600, 200, 200);
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_YELLOW);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_CYAN);
    init_pair(6, COLOR_WHITE, COLOR_GREEN);
}

void ClientLayout::drawShip(int16_t y, int16_t x, uint8_t dir, WINDOW* window){
    char c;
    switch (dir) {
        case DIR_UP:
            c = '^';
            mvwaddch(window, y, x, c);
            for (size_t i=0; i<SHIP_HALFSIZE_IN_PIXELS; i++) {
                for (size_t j=0; j<SHIP_HALFSIZE_IN_PIXELS; j++) {
                    mvwaddch(window, y-i-1, x-j-1, c);
                    mvwaddch(window, y+i+1, x+j+1, c);
                    mvwaddch(window, y-i-1, x+j+1, c);
                    mvwaddch(window, y+i+1, x-j-1, c);
                }
            }
            break;
        case DIR_DOWN:
            c = 'v';
            mvwaddch(window, y, x, c);
            for (size_t i=0; i<SHIP_HALFSIZE_IN_PIXELS; i++) {
                for (size_t j=0; j<SHIP_HALFSIZE_IN_PIXELS; j++) {
                    mvwaddch(window, y-i-1, x-j-1, c);
                    mvwaddch(window, y+i+1, x+j+1, c);
                    mvwaddch(window, y-i-1, x+j+1, c);
                    mvwaddch(window, y+i+1, x-j-1, c);
                }
            }
            break;
        case DIR_LEFT:
            c = '<';
            mvwaddch(window, y, x, c);
            for (size_t i=0; i<SHIP_HALFSIZE_IN_PIXELS; i++) {
                for (size_t j=0; j<SHIP_HALFSIZE_IN_PIXELS; j++) {
                    mvwaddch(window, y-i-1, x-j-1, c);
                    mvwaddch(window, y+i+1, x+j+1, c);
                    mvwaddch(window, y-i-1, x+j+1, c);
                    mvwaddch(window, y+i+1, x-j-1, c);
                }
            }
            break;
        case DIR_RIGHT:
            c = '>';
            mvwaddch(window, y, x, c);
            for (size_t i=0; i<SHIP_HALFSIZE_IN_PIXELS; i++) {
                for (size_t j=0; j<SHIP_HALFSIZE_IN_PIXELS; j++) {
                    mvwaddch(window, y-i-1, x-j-1, c);
                    mvwaddch(window, y+i+1, x+j+1, c);
                    mvwaddch(window, y-i-1, x+j+1, c);
                    mvwaddch(window, y+i+1, x-j-1, c);
                }
            }
            break;
        default:
            break;
    }
}

void ClientLayout::drawProjectile(int16_t y, int16_t x, uint8_t dir, WINDOW* window){
    char c;
    switch (dir) {
        case DIR_UP:
            c = '|';
            mvwaddch(window, y, x, c);
            for (size_t i=0; i<OBJECT_HALFSIZE_IN_PIXELS; i++) {
                for (size_t j=0; j<OBJECT_HALFSIZE_IN_PIXELS; j++) {
                    mvwaddch(window, y-i-1, x-j-1, c);
                    mvwaddch(window, y+i+1, x+j+1, c);
                    mvwaddch(window, y-i-1, x+j+1, c);
                    mvwaddch(window, y+i+1, x-j-1, c);
                }
            }
            break;
        case DIR_DOWN:
            c = '|';
            mvwaddch(window, y, x, c);
            for (size_t i=0; i<OBJECT_HALFSIZE_IN_PIXELS; i++) {
                for (size_t j=0; j<OBJECT_HALFSIZE_IN_PIXELS; j++) {
                    mvwaddch(window, y-i-1, x-j-1, c);
                    mvwaddch(window, y+i+1, x+j+1, c);
                    mvwaddch(window, y-i-1, x+j+1, c);
                    mvwaddch(window, y+i+1, x-j-1, c);
                }
            }
            break;
        case DIR_LEFT:
            c = '-';
            mvwaddch(window, y, x, c);
            for (size_t i=0; i<OBJECT_HALFSIZE_IN_PIXELS; i++) {
                for (size_t j=0; j<OBJECT_HALFSIZE_IN_PIXELS; j++) {
                    mvwaddch(window, y-i-1, x-j-1, c);
                    mvwaddch(window, y+i+1, x+j+1, c);
                    mvwaddch(window, y-i-1, x+j+1, c);
                    mvwaddch(window, y+i+1, x-j-1, c);
                }
            }
            break;
        case DIR_RIGHT:
            c = '-';
            mvwaddch(window, y, x, c);
            for (size_t i=0; i<OBJECT_HALFSIZE_IN_PIXELS; i++) {
                for (size_t j=0; j<OBJECT_HALFSIZE_IN_PIXELS; j++) {
                    mvwaddch(window, y-i-1, x-j-1, c);
                    mvwaddch(window, y+i+1, x+j+1, c);
                    mvwaddch(window, y-i-1, x+j+1, c);
                    mvwaddch(window, y+i+1, x-j-1, c);
                }
            }
            break;
        default:
            break;
    }
}


void ClientLayout::drawBomb(int16_t y, int16_t x, WINDOW* window){
    char c;
    c = 'o';
    mvwaddch(window, y, x, c);
    for (size_t i=0; i<OBJECT_HALFSIZE_IN_PIXELS; i++) {
        mvwaddch(window, y-i-1, x, c);
        mvwaddch(window, y+i+1, x, c);
        mvwaddch(window, y, x+i+1, c);
        mvwaddch(window, y, x-i-1, c);
        for (size_t j=0; j<OBJECT_HALFSIZE_IN_PIXELS; j++) {
            mvwaddch(window, y-i-1, x-j-1, c);
            mvwaddch(window, y+i+1, x+j+1, c);
            mvwaddch(window, y-i-1, x+j+1, c);
            mvwaddch(window, y+i+1, x-j-1, c);
        }
    }
}

void ClientLayout::drawPowerUp(int16_t y, int16_t x, WINDOW* window){
    char c;
    c = '*';
    mvwaddch(window, y, x, c);
    for (size_t i=0; i<OBJECT_HALFSIZE_IN_PIXELS; i++) {
        mvwaddch(window, y-i-1, x, c);
        mvwaddch(window, y+i+1, x, c);
        mvwaddch(window, y, x+i+1, c);
        mvwaddch(window, y, x-i-1, c);
        for (size_t j=i+1; j<OBJECT_HALFSIZE_IN_PIXELS; j++) {
            mvwaddch(window, y-i-1, x-j-1, c);
            mvwaddch(window, y+i+1, x+j+1, c);
            mvwaddch(window, y-i-1, x+j+1, c);
            mvwaddch(window, y+i+1, x-j-1, c);
        }
    }
}

void ClientLayout::handleResize([[maybe_unused]] int sig){
    endwin();
    deleteWindow(window);
    //int mx, my;
    //getmaxyx(stdscr, my, mx);
    //window = newwin(my, mx, 0, 0);
    clear();
    refresh();
}

WINDOW * ClientLayout::drawGame(GameData gd, uint8_t id)
{
    WINDOW * window = NULL;
    
    int totalRowVisitable, totalColumnVisitable;
    int startingRow = 0, startingColumn = 0;
    int color = 1;
    int16_t centrex=-1, centrey=-1;
    
    getmaxyx(stdscr, totalRowVisitable, totalColumnVisitable);
    
    for (auto ship : gd.ships) {
        if(ship.unique_id == id)
        {
            centrex = ship.x;
            centrey = ship.y;
            startingRow = centrey - totalRowVisitable/2;
            startingColumn = centrex - totalColumnVisitable/2;
            break;
        }
    }
    
    if(centrex==-1||centrey==-1)
        return NULL;
    
    window = newwin(totalRowVisitable, totalColumnVisitable, 0, 0);
    
    wbkgd(window, COLOR_PAIR(7));
    
    for (auto ship : gd.ships) {
        
        if(ship.unique_id == id)
            color = 1;
        else
            color = ship.unique_id % SHIP_COLORS + 2;
        
        wattron(window, COLOR_PAIR(color));
        drawShip(ship.y-startingRow, ship.x-startingColumn, ship.dir, window);
        wattroff(window, COLOR_PAIR(color));
        
    }
    for (auto projectile : gd.projectiles) {
        
        if(projectile.unique_id == id)
            color = 1;
        else
            color = projectile.unique_id % SHIP_COLORS + 2;
        
        wattron(window, COLOR_PAIR(color));
        drawProjectile(projectile.y-startingRow, projectile.x-startingColumn, projectile.dir, window);
        wattroff(window, COLOR_PAIR(color));
        
    }
    
    color = 6;
    for (auto bomb : gd.bombs) {
        wattron(window, COLOR_PAIR(color));
        drawBomb(bomb.y-startingRow, bomb.x-startingColumn, window);
        wattroff(window, COLOR_PAIR(color));
    }
    for (auto powerup : gd.powerups) {
        wattron(window, COLOR_PAIR(color));
        drawPowerUp(powerup.y-startingRow, powerup.x-startingColumn, window);
        wattroff(window, COLOR_PAIR(color));
    }
    
    drawBorders(window, centrey, centrex, totalRowVisitable, totalColumnVisitable);
    
    return window;
}


void ClientLayout::drawBorders(WINDOW* window, int centrey, int centrex, int totalRowVisitable, int totalColumnVisitable)
{
    int startingRow = 0, startingColumn = 0;
    // Top border
    if (centrey - (totalRowVisitable / 2) < -1) {
        startingRow = centrey - (totalRowVisitable / 2);

        int startCol = centrex - (totalColumnVisitable / 2) < 0 ? centrex - (totalColumnVisitable / 2) : 0;
        int endCol = centrex + (totalColumnVisitable / 2) > MAP_WIDTH + 1 ?
                      (MAP_WIDTH + 1 - centrex) + (totalColumnVisitable / 2) : totalColumnVisitable;
        
        for (int i = abs(startCol); i < endCol; i++) {
            mvwaddch(window, abs(startingRow) - 1, i, MAIN_MENU_BORDER_CHARACTER);
        }
    }
    // Bottom border
    if (centrey + (totalRowVisitable / 2) >= MAP_HEIGHT) {
        startingRow = (MAP_HEIGHT + 1 - centrey) + (totalRowVisitable / 2);

        int startCol = centrex - (totalColumnVisitable / 2) < 0 ? centrex - (totalColumnVisitable / 2) : 0;
        int endCol = centrex + (totalColumnVisitable / 2) > MAP_WIDTH +1 ?
                      (MAP_WIDTH + 1 - centrex) + (totalColumnVisitable / 2) : totalColumnVisitable;
        
        for (int i = abs(startCol); i < endCol; i++) {
            mvwaddch(window, startingRow - 1, i, MAIN_MENU_BORDER_CHARACTER);
        }
    }
    // Left border
    if (centrex - (totalColumnVisitable / 2) < -1) {
        startingColumn = centrex - (totalColumnVisitable / 2);

        int startRow = centrey - (totalRowVisitable / 2) < 0 ? centrey - (totalRowVisitable / 2) : 0;
        int endRow = centrey + (totalRowVisitable / 2) >= MAP_HEIGHT + 1 ?
                    (MAP_HEIGHT + 1 - centrey) + (totalRowVisitable / 2) : totalRowVisitable;
        
        for (int i = abs(startRow) - 1; i < endRow; i++) {
            mvwaddch(window, i, abs(startingColumn) - 1, MAIN_MENU_BORDER_CHARACTER);
        }
    }
    // Right border
    if (centrex + (totalColumnVisitable / 2) > MAP_WIDTH) {
        startingColumn = (MAP_WIDTH + 1 - centrex) + (totalColumnVisitable / 2);

        int startRow = centrey - (totalRowVisitable / 2) < 0  ? centrey - (totalRowVisitable / 2) : 0;
        int endRow = centrey + (totalRowVisitable / 2) >= MAP_HEIGHT + 1 ?
                      (MAP_HEIGHT + 1 - centrey) + (totalRowVisitable / 2) : totalRowVisitable;
        
        for (int i = abs(startRow); i < endRow; i++) {
            mvwaddch(window, i, startingColumn - 1, MAIN_MENU_BORDER_CHARACTER);
        }
    }
    
}

void ClientLayout::drawEndGame(uint8_t status, std::string winnername)
{
    if(status == WINNER){
        displayTextInCentre(WINNER_TEXT);
    }else if(status == LOSER){
        displayTextInCentre(LOSER_TEXT + winnername);
    }else{
        displayTextInCentre(ERROR_TEXT);
    }
}

void ClientLayout::displayTextInCentre(std::string s)
{
    WINDOW * win = modalLayout(1);
    mvwprintw(win, 2, 3, s.c_str());
    wrefresh(win);
    sleep(PROMPT_SCREEN_DELAY_SEC);
    wborder(stdscr, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    refresh();
    deleteWindow(win);
}

WINDOW * ClientLayout::modalLayout(int height)
{
    int totalRowVisitable, totalColumnVisitable, windowStartingX,
            windowStartingY, correctHeight = height + 4, width;
    getmaxyx(stdscr, totalRowVisitable, totalColumnVisitable);

    wborder(stdscr,
            MAIN_MENU_BORDER_CHARACTER, MAIN_MENU_BORDER_CHARACTER,
            MAIN_MENU_BORDER_CHARACTER, MAIN_MENU_BORDER_CHARACTER,
            MAIN_MENU_BORDER_CHARACTER, MAIN_MENU_BORDER_CHARACTER,
            MAIN_MENU_BORDER_CHARACTER, MAIN_MENU_BORDER_CHARACTER);
    refresh();

    windowStartingX = totalColumnVisitable / 4;
    windowStartingY =  totalRowVisitable / 3;
    width = totalColumnVisitable / 2;

    WINDOW * menuWindow;
    menuWindow = newwin(correctHeight, width, windowStartingY, windowStartingX);
    wbkgd(menuWindow, COLOR_PAIR(7));
    
    wborder(menuWindow,
            MAIN_MENU_BORDER_CHARACTER, MAIN_MENU_BORDER_CHARACTER,
            MAIN_MENU_BORDER_CHARACTER, MAIN_MENU_BORDER_CHARACTER,
            MAIN_MENU_BORDER_CHARACTER, MAIN_MENU_BORDER_CHARACTER,
            MAIN_MENU_BORDER_CHARACTER, MAIN_MENU_BORDER_CHARACTER);
    
    return menuWindow;
}
