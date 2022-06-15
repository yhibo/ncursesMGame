//
//  Server.hpp
//  Server
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#ifndef Server_hpp
#define Server_hpp

#include <iostream>
#include "../Common/Types.hpp"
#include "Client.hpp"
#include "GameServer.hpp"
#include "ServerAPI.hpp"
#include "sys/socket.h"
#include <thread>

class Server {
private:
    bool running;
    int nextuserid;
    int portNo;
    int server_socket;
    sockaddr_in servAddr;
    std::vector<Client *> vpclients;
    std::thread sockth;
    std::vector<std::thread> th_clients;
    std::mutex mtx;
    GameServer gameserver;
    void acceptNewClients();
    void initServerSocket();
public:
    Server(int port);
    ~Server();
    void run();
};

#endif /* Server_hpp */
