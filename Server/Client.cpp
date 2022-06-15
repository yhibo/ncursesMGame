//
//  Client.cpp
//  Server
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#include "Client.hpp"

Client::Client(int sockfd, sockaddr_in cliAddr_, uint8_t id_)
{
    this->cli_socket = sockfd;
    this->cliAddr = cliAddr_;
    this->id = id_;
    kills = 0;
}

Client::~Client()
{
    clith.join();
    close(cli_socket);
}

uint8_t Client::getID()
{
    return id;
}

int Client::getSocket()
{
    return cli_socket;
}

sockaddr_in Client::getAddr()
{
    return cliAddr;
}

std::string Client::getName()
{
    return name;
}

void Client::setName(const char * s)
{
    name = s;
}
