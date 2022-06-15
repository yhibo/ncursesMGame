//
//  GameServer.cpp
//  Server
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#include "GameServer.hpp"


GameServer::GameServer(std::vector<Client*> * pclients_, std::mutex * pmtx_) : pvpclients(pclients_), pmtx(pmtx_) {}

GameServer::~GameServer(){
    running = false;
    th_powerups.join();
    th_bombs.join();
    th_input.join();
}

void GameServer::start()
{
    running = true;
    
    th_input = std::thread(&GameServer::handleInputFromClients,this);
    th_bombs = std::thread(&GameServer::generateBombs,this);
    th_powerups = std::thread(&GameServer::generatePowerUps,this);
    
    while (true) {
        gameloop();
    }
}

void GameServer::addNewClientShip(Client * c)
{
    Ship newship(c->getID());
    assignRandomPosition(newship);
    gd.ships.push_back(newship);
}

void GameServer::assignRandomPosition(Object &obj)
{
    int16_t x, y;
    Object checker = obj;
    obj.x = -SHIP_HALFSIZE_IN_PIXELS;
    obj.y = -SHIP_HALFSIZE_IN_PIXELS;
    do
    {
        x = rand() % (MAP_WIDTH - 2*obj.getHalfsize() - 1);
        x = x + obj.getHalfsize();
        y = rand() % (MAP_HEIGHT - 2*obj.getHalfsize() - 1);
        y = y + obj.getHalfsize();
        checker.x = x;
        checker.y = y;
    } while (!isPositionValid(checker));
    obj.x = x;
    obj.y = y;
}


bool GameServer::isPositionValid(Object obj)
{
    for (auto &ship : gd.ships)
    {
        if(obj.collidesWith(ship)) return false;
    }
    for (auto &projectile : gd.projectiles)
    {
        if(obj.collidesWith(projectile)) return false;
    }
    for (auto &powerUp : gd.powerups)
    {
        if(obj.collidesWith(powerUp)) return false;
    }
    for (auto &bomb : gd.bombs)
    {
        if(obj.collidesWith(bomb)) return false;
    }
    return true;
}


void GameServer::initClient(Client * c)
{
    std::unique_lock<std::mutex> lck(*pmtx);
    
    if(serverapi.sendIdToClient(c))
    {
        removeClient(c);
        return;
    }
    
    if(serverapi.getNameFromClient(c))
    {
        removeClient(c);
        return;
    }
    
    addNewClientShip(c);
    
    bool error = false;
    do
    {
        error = serverapi.sendGameDataToClient(c, gd);
    }while(error);
    
    auto ipAddr = c->getAddr();
    char ipAddrBuffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ipAddr, ipAddrBuffer, INET_ADDRSTRLEN);
    printf("Connection: IP: %s, ID: %d.\n", ipAddrBuffer, c->getID());
    
    lck.unlock();
}

void GameServer::removeClient(Client * c)
{
    for (auto it=pvpclients->begin(); it!=pvpclients->end(); it++)
    {
        if (*it == c)
        {
            deleteClientShip(*it);
            delete *it;
            pvpclients->erase(it--);
            return;;
        }
    }
}

void GameServer::gameloop()
{
    unsigned int i=0;
    setKillsNull();
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(GAME_UPDATE_RATE_NS));
        std::unique_lock<std::mutex> lck(*pmtx);
        moveProjectiles();
        if(i%GAME_UPDATE_PROJ_SHIP_RATIO == 0)
            moveShips();
        checkForProjectilesCollisions();
        if(i++%GAME_UPDATE_PROJ_SHIP_RATIO == 0)
            checkForShipsCollisions();
        if(checkForWinners())
        {
            printf("Someone won.\n");
            break;
        }
        sendGameDataToClients();
        lck.unlock();
    }
    printf("Out of game loop.\n");
    std::unique_lock<std::mutex> lck(*pmtx);
    sendEndGameToClients();
    lck.unlock();
}

void GameServer::sendEndGameToClients()
{
    for (auto it=pvpclients->begin(); it!=pvpclients->end(); it++)
    {
        if ((*it)->kills == KILLS_TO_WIN)
        {
            if (serverapi.sendWinnerStatusToClient(*it))
            {
                deleteClientShip(*it);
                delete *it;
                pvpclients->erase(it--);
            }
            continue;
        }
        if (serverapi.sendLoserStatusToClient(*it, winnername))
        {
            deleteClientShip(*it);
            delete *it;
            pvpclients->erase(it--);
        }
    }
}

void GameServer::setKillsNull()
{
    for (auto it=pvpclients->begin(); it!=pvpclients->end(); it++)
    {
        (*it)->kills = 0;
    }
}

bool GameServer::checkForWinners()
{
    for (auto it=pvpclients->begin(); it!=pvpclients->end(); it++)
    {
        if ((*it)->kills == KILLS_TO_WIN)
        {
            winnername = (*it)->getName();
            return true;
        }
    }
    return false;
}

void GameServer::moveProjectiles()
{
    for (auto& projectile : gd.projectiles)
    {
        projectile.move();
    }
    for (auto&ship : gd.ships)
    {
        if(ship.shot)
        {
            addShipProjectiles(ship, gd.projectiles);
            ship.shot = false;
        }
    }
}

void GameServer::moveShips()
{
    for (auto& ship : gd.ships)
    {
        ship.move();
    }
}

void GameServer::checkForProjectilesCollisions()
{
    std::vector<Projectile> aux;
    
    for (auto pit=gd.projectiles.begin(); pit!=gd.projectiles.end(); pit++)
    {
        
        if (pit->collidesWithBorder())
        {
            gd.projectiles.erase(pit--);
            goto endouterfor;
        }
        
        for (auto sit=gd.ships.begin(); sit!=gd.ships.end(); sit++)
        {
            if(pit->collidesWith(*sit))
            {
                printf("Someone died.\n");
                if(pit->unique_id!=sit->unique_id)
                    incrementKills(pit->unique_id);
                resetKills(sit->unique_id);
                assignRandomPosition(*sit);
                gd.projectiles.erase(pit--);
                goto endouterfor;
            }
        }
        for (auto bit=gd.bombs.begin(); bit!=gd.bombs.end(); bit++)
        {
            if(pit->collidesWith(*bit))
            {
                uint8_t id = pit->unique_id;
                gd.projectiles.erase(pit--);
                addBombProjectiles(*bit, id, aux);
                gd.bombs.erase(bit--);
                bcond.notify_one();
                goto endouterfor;
            }
        }
        for (auto puit=gd.powerups.begin(); puit!=gd.powerups.end(); puit++)
        {
            if(pit->collidesWith(*puit))
            {
                setShipPowup(pit->unique_id);
                gd.powerups.erase(puit--);
                pcond.notify_one();
                gd.projectiles.erase(pit--);
                goto endouterfor;
            }
        }
        
        endouterfor:
        continue;
    }
    
    gd.projectiles.insert(gd.projectiles.end(), aux.begin(), aux.end());
}

void GameServer::checkForShipsCollisions()
{
    for (auto sit=gd.ships.begin(); sit!=gd.ships.end(); sit++)
    {
        
        if (sit->collidesWithBorder())
        {
            resetKills(sit->unique_id);
            assignRandomPosition(*sit);
        }
        
        for (auto sit2=sit+1; sit2!=gd.ships.end(); sit2++)
        {
            if(sit->collidesWith(*sit2))
            {
                resetKills(sit2->unique_id);
                assignRandomPosition(*sit2);
                resetKills(sit->unique_id);
                assignRandomPosition(*sit);
            }
        }
        
        for (auto bit=gd.bombs.begin(); bit!=gd.bombs.end(); bit++)
        {
            if(sit->collidesWith(*bit))
            {
                addBombProjectiles(*bit, sit->unique_id, gd.projectiles);
                gd.bombs.erase(bit--);
                bcond.notify_one();
                resetKills(sit->unique_id);
                assignRandomPosition(*sit);
            }
        }
        for (auto puit=gd.powerups.begin(); puit!=gd.powerups.end(); puit++)
        {
            if(sit->collidesWith(*puit))
            {
                setShipPowup(sit->unique_id);
                gd.powerups.erase(puit--);
                pcond.notify_one();
            }
        }
    }
}

void GameServer::setShipPowup(uint8_t id)
{
    for (auto&s : gd.ships) {
        if (s.unique_id == id) {
            s.powup = true;
        }
    }
}

void GameServer::incrementKills(uint8_t id)
{
    for (auto it=pvpclients->begin(); it!=pvpclients->end(); it++)
    {
        if ((*it)->getID()==id)
        {
            (*it)->kills++;
        }
    }
}

void GameServer::resetKills(uint8_t id)
{
    for (auto it=pvpclients->begin(); it!=pvpclients->end(); it++)
    {
        if ((*it)->getID()==id)
        {
            (*it)->kills = 0;
        }
    }
}

void GameServer::addShipProjectiles(Ship& s, std::vector<Projectile>& aux)
{
    int sz = (Projectile()).getHalfsize();
    if (s.powup) {
        aux.emplace_back(s.x+s.getHalfsize()+sz+2, s.y, s.unique_id, DIR_RIGHT);
        aux.emplace_back(s.x-s.getHalfsize()-sz-2, s.y, s.unique_id, DIR_LEFT);
        aux.emplace_back(s.x, s.y+s.getHalfsize()+sz+2, s.unique_id, DIR_DOWN);
        aux.emplace_back(s.x, s.y-s.getHalfsize()-sz-2, s.unique_id, DIR_UP);
        s.powupcounter++;
        if (s.powupcounter == POWERUP_DURATION)
        {
            s.powup = false;
            s.powupcounter = 0;
        }
    }
    else{
        switch (s.dir) {
            case DIR_RIGHT:
                aux.emplace_back(s.x+s.getHalfsize()+sz+2, s.y, s.unique_id, DIR_RIGHT);
                break;
            case DIR_LEFT:
                aux.emplace_back(s.x-s.getHalfsize()-sz-2, s.y, s.unique_id, DIR_LEFT);
                break;
            case DIR_DOWN:
                aux.emplace_back(s.x, s.y+s.getHalfsize()+sz+2, s.unique_id, DIR_DOWN);
                break;
            case DIR_UP:
                aux.emplace_back(s.x, s.y-s.getHalfsize()-sz-2, s.unique_id, DIR_UP);
                break;
            default:
                break;
        }
    }
}

void GameServer::addBombProjectiles(Bomb b, uint8_t id, std::vector<Projectile>& aux)
{
    aux.emplace_back(b.x+b.getHalfsize()+1, b.y, id, DIR_RIGHT);
    aux.emplace_back(b.x-b.getHalfsize()-1, b.y, id, DIR_LEFT);
    aux.emplace_back(b.x, b.y+b.getHalfsize()+1, id, DIR_DOWN);
    aux.emplace_back(b.x, b.y-b.getHalfsize()-1, id, DIR_UP);
}

void GameServer::sendGameDataToClients()
{
    for (auto it=pvpclients->begin(); it!=pvpclients->end(); it++)
    {
        if (serverapi.sendGameDataToClient(*it, gd))
        {
            deleteClientShip(*it);
            delete *it;
            pvpclients->erase(it--);
        }
    }
}

void GameServer::handleInputFromClients()
{
    while(true)
    {
        std::unique_lock<std::mutex> lck(*pmtx);
        if (!running) {
            return;
        }
        for (auto it=pvpclients->begin(); it!=pvpclients->end(); it++)
        {
            uint8_t header;
            serverapi.setSocketBlockingEnabled((*it)->getSocket(), false);
            int response = serverapi.readHeaderFromClient(*it, header);
            serverapi.setSocketBlockingEnabled((*it)->getSocket(), true);
            if(response<0)
            {
                if (errno == EAGAIN)
                {
                    continue;
                }
                else
                {
                    deleteClientShip(*it);
                    delete *it;
                    pvpclients->erase(it--);
                    continue;
                }
            }
            if(header == H_CHANGEDIR)
            {
                uint8_t dir;
                if(serverapi.readDirFromClient(*it, dir)<0)
                    continue;
                printf("User: %s, Dir: %d\n", ((*it)->getName()).c_str(), dir);
                if (dir==SHOOT_CODE)
                    setShipShotTrue((*it)->getID());
                else
                    changeShipDir((*it)->getID(), dir);
                
            }
        }
        lck.unlock();
        std::this_thread::sleep_for(std::chrono::nanoseconds(GAME_READ_USER_INPUT_UPDATE_RATE_NS));
    }
}

void GameServer::deleteClientShip(Client * c)
{
    
    auto id = c->getID();
    
    for (auto it=gd.ships.begin(); it!=gd.ships.end(); it++)
    {
        if(it->unique_id == id)
        {
            gd.ships.erase(it--);
            break;
        }
    }
}

void GameServer::setShipShotTrue(uint8_t id)
{
    for (auto&s : gd.ships) {
        if (s.unique_id == id) {
            s.shot = true;
        }
    }
}

void GameServer::changeShipDir(uint8_t id, uint8_t dir)
{
    for (auto&s : gd.ships) {
        if (s.unique_id == id) {
            s.dir = dir;
        }
    }
}


void GameServer::generateBombs()
{
    while(true)
    {
        std::unique_lock<std::mutex> lck(*pmtx);
        
        while (gd.bombs.size() >= MAXIMUM_AMOUNT_OF_BOMBS_ON_SCREEN && running) {
            bcond.wait(lck);
        }
        
        if (!running) {
            return;
        }
        
        Bomb b;
        assignRandomPosition(b);
        gd.bombs.push_back(b);
        
        lck.unlock();
        
        
        long sleep_time = rand() % (MAXIMUM_BOMB_INTERVAL_SECS_MS + 1 - MINIMUM_BOMB_INTERVAL_SECS_MS) + MINIMUM_BOMB_INTERVAL_SECS_MS;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
}

void GameServer::generatePowerUps()
{
    while(true)
    {
        std::unique_lock<std::mutex> lck(*pmtx);
        
        while (gd.powerups.size() >= MAXIMUM_AMOUNT_OF_POWERUP_ON_SCREEN && running) {
            pcond.wait(lck);
        }
        
        if (!running) {
            return;
        }
        
        PowerUp p;
        assignRandomPosition(p);
        gd.powerups.push_back(p);
        
        lck.unlock();
        
        long sleep_time = rand() % (MAXIMUM_POWERUP_INTERVAL_SECS_MS + 1 - MINIMUM_POWERUP_INTERVAL_SECS_MS) + MINIMUM_POWERUP_INTERVAL_SECS_MS;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
}
