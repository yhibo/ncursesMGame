//
//  ServerAPI.cpp
//  Server
//
//  Created by Yhibo Blado Radlovacki Parisi on 25/05/2022.
//

#include "ServerAPI.hpp"

int ServerAPI::sendIdToClient(Client * c)
{
    int sockfd = c->getSocket();
    
    uint8_t h = H_ID;
    if(send(sockfd, &h, sizeof(h), 0)<0)
        return -1;
    
    uint8_t id = c->getID();
    if(send(sockfd, &id, sizeof(id), 0)<0)
        return -1;
    
    return 0;
}

int ServerAPI::sendGameDataToClient(Client * c, GameData gd)
{
    int sockfd = c->getSocket();
    
    uint8_t h = H_DATA;
    if(send(sockfd, &h, sizeof(h), 0)<0)
        return -1;
    
    
    unsigned long data_bytes = SHIP_BYTES*gd.ships.size()
                            + PROJECTILE_BYTES*gd.projectiles.size()
                            + POWERUP_BYTES*gd.powerups.size()
                            + BOMB_BYTES*gd.bombs.size();
    
    
    uint8_t sizesbuffer[INT_BYTES];
    SerDes::serializeInt(sizesbuffer, htonl(gd.ships.size()));
    if(write(sockfd, sizesbuffer, INT_BYTES)<0) return -1;
    SerDes::serializeInt(sizesbuffer, htonl(gd.projectiles.size()));
    if(write(sockfd, sizesbuffer, INT_BYTES)<0) return -1;
    SerDes::serializeInt(sizesbuffer, htonl(gd.powerups.size()));
    if(write(sockfd, sizesbuffer, INT_BYTES)<0) return -1;
    SerDes::serializeInt(sizesbuffer, htonl(gd.bombs.size()));
    if(write(sockfd, sizesbuffer, INT_BYTES)<0) return -1;
    
    
    uint8_t data[data_bytes];
    SerDes::serializeGameDataToNetwork(data, gd);
    if (write(sockfd,data,data_bytes)<0) return -1;
    
    return 0;
}

int ServerAPI::sendWinnerStatusToClient(Client * c)
{
    int sockfd = c->getSocket();
    
    uint8_t h = H_WINNER;
    if(send(sockfd, &h, sizeof(h), 0)<0)
        return -1;
    
    return 0;
}

int ServerAPI::sendLoserStatusToClient(Client * c, std::string winnername)
{
    int sockfd = c->getSocket();
    
    uint8_t h = H_LOSER;
    if(send(sockfd, &h, sizeof(h), 0)<0)
        return -1;
    
    h = H_NAME;
    if(send(sockfd, &h, sizeof(h), 0)<0)
        return -1;
    
    uint8_t len = strlen(winnername.c_str())+1;
    if(send(sockfd, &len, sizeof(len), 0)<0)
        return -1;
    
    if(send(sockfd, winnername.c_str(), len, 0)<0)
        return -1;
    
    return 0;
}

bool ServerAPI::setSocketBlockingEnabled(int sockFd, bool blocking)
{
    int flags;

    if (sockFd < 0) {
        return false;
    }
    flags = fcntl(sockFd, F_GETFL, 0);
    if (flags < 0) {
        return false;
    }
    flags = blocking ? (flags&~O_NONBLOCK) : (flags|O_NONBLOCK);
    return (fcntl(sockFd, F_SETFL, flags) == 0) ? true : false;
}

int ServerAPI::readHeaderFromClient(Client * c, uint8_t& header)
{
    uint8_t header_buffer[HEADER_BYTES];
    int response = (int) recv(c->getSocket(), header_buffer, HEADER_BYTES, 0);
    header = header_buffer[0];
    
    return response;
}

int ServerAPI::readDirFromClient(Client * c, uint8_t& dir)
{
    return (int) recv(c->getSocket(), &dir, DIR_BYTES, 0);
}

int ServerAPI::getNameFromClient(Client * c)
{
    
    uint8_t h;
    if(recv(c->getSocket(), &h, sizeof(h), 0)<0)
        return -1;
    
    if (h!=H_NAME)
        return -1;
    
    uint8_t namelen;
    if(recv(c->getSocket(), &namelen, sizeof(namelen), 0)<0)
        return -1;
    
    char name[namelen];
    if(recv(c->getSocket(), &name, namelen, 0)<0)
        return -1;
    
    printf("Name: %s\n",name);
    c->setName(name);
    
    return 0;
}
