//
//  GameServer.hpp
//  Server
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#ifndef GameServer_hpp
#define GameServer_hpp

#include "../Common/SerDes.hpp"
#include "Client.hpp"
#include "ServerAPI.hpp"
#include <thread>

class GameServer {
private:
    bool running;
    ServerAPI serverapi;
    std::vector<Client *> * pvpclients;
    std::mutex * pmtx;
    std::thread th_input;
    std::thread th_bombs;
    std::thread th_powerups;
    std::condition_variable bcond;
    std::condition_variable pcond;
    std::string winnername;
    GameData gd;
public:
    ~GameServer();
    GameServer(std::vector<Client*> *, std::mutex *);
    void start();
    void initClient(Client * c);
    void addNewClientShip(Client * c);
    void assignRandomPosition(Object &obj);
    void sendGameDataToClients();
    void handleInputFromClients();
    void moveProjectiles();
    void moveShips();
    void setKillsNull();
    void addShipProjectiles(Ship&, std::vector<Projectile>& aux);
    void addBombProjectiles(Bomb, uint8_t, std::vector<Projectile>& aux);
    void setShipPowup(uint8_t);
    void checkForProjectilesCollisions();
    void checkForShipsCollisions();
    void changeShipDir(uint8_t, uint8_t);
    void setShipShotTrue(uint8_t);
    bool checkForWinners();
    void sendEndGameToClients();
    void moveObjects();
    void gameloop();
    void incrementKills(uint8_t);
    void resetKills(uint8_t);
    void removeClient(Client *);
    void deleteClientShip(Client *);
    bool isPositionValid(Object obj);
    void generateBombs();
    void generatePowerUps();
};

#endif /* GameServer_hpp */
