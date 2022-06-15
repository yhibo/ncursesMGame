//
//  Server.cpp
//  Server
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#include "Server.hpp"


//init TCP server
Server::Server(int port) : gameserver(&vpclients, &mtx)
{
    nextuserid = 0;
    portNo = port;
}

Server::~Server()
{
    running = false;
    sockth.join();
    for (auto&pclient : vpclients) {
        delete pclient;
    }
    close(server_socket);
}

void Server::run()
{
    running = true;
    
    sockth = std::thread(&Server::initServerSocket, this);
    
    gameserver.start();
}


void Server::initServerSocket()
{
    //create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        error("ERROR opening socket");
    }
    //bind socket to port
    bzero((char *)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(portNo);
    int val = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (bind(server_socket, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        error("ERROR on binding");
    }
    //listen for connections
    listen(server_socket, 0);
    acceptNewClients();
}


void Server::acceptNewClients()
{
    int client_socket;
    socklen_t clilen;
    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    while (true)
    {
        if(!running)
            return;
        client_socket = accept(server_socket, (struct sockaddr *)&cli_addr, &clilen);
        if (client_socket < 0)
        {
            error("ERROR on accept");
        }
        std::unique_lock<std::mutex> lock(mtx);
        Client * pclient = new Client(client_socket, cli_addr, nextuserid++);
        vpclients.push_back(pclient);
        pclient->clith = std::thread(&GameServer::initClient, &gameserver, pclient);
        lock.unlock();
    }
}





