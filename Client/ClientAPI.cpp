//
//  ClientAPI.cpp
//  Client
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#include "ClientAPI.hpp"

ClientAPI::~ClientAPI()
{
    close(sockfd);
}

void ClientAPI::init(char* host, char* port)
{
    portno = std::atoi(port);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    server = gethostbyname(host);
    if (server == NULL)
    {
        error("ERROR, no such host");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
}

void ClientAPI::connectToServer()
{
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }
}

// read gamedata from server
int ClientAPI::readGameDataFromServer(GameData &gd)
{
    int sizes[NVECTORS];
    uint8_t sizesbuffer[INT_BYTES];
    int n = (int) recv(sockfd, sizesbuffer, INT_BYTES, 0);
    if(n<0) return -1;
    SerDes::deserializeInt(sizesbuffer, sizes[0]);
    n = (int) recv(sockfd, sizesbuffer, INT_BYTES, 0);
    if(n<0) return -1;
    SerDes::deserializeInt(sizesbuffer, sizes[1]);
    n = (int) recv(sockfd, sizesbuffer, INT_BYTES, 0);
    if(n<0) return -1;
    SerDes::deserializeInt(sizesbuffer, sizes[2]);
    n = (int) recv(sockfd, sizesbuffer, INT_BYTES, 0);
    if(n<0) return -1;
    SerDes::deserializeInt(sizesbuffer, sizes[3]);

    for(int i=0; i<NVECTORS; i++) sizes[i] = ntohl(sizes[i]);

    int data_bytes = SHIP_BYTES*sizes[0] 
                    + PROJECTILE_BYTES*sizes[1] 
                    + POWERUP_BYTES*sizes[2] 
                    + BOMB_BYTES*sizes[3];

    uint8_t buffer[data_bytes];
    n = (int) recv(sockfd, buffer, data_bytes, 0);

    if(n<0) return -1;
    SerDes::deserializeGameDataFromNetwork(buffer, sizes, gd);

    return 0;
}

int ClientAPI::readIDFromServer(uint8_t& id)
{
    uint8_t buffer[ID_BYTES];
    int n = (int) recv(sockfd, buffer, ID_BYTES, 0);
    if(n<0) return -1;
    SerDes::deserializeUint8(buffer, id);
    return 0;
}

int ClientAPI::sendInputToServer(uint8_t input)
{
    uint8_t header_buffer[HEADER_BYTES];
    SerDes::serializeUint8(header_buffer, H_CHANGEDIR);
    int n = (int) send(sockfd, header_buffer, HEADER_BYTES, 0);
    if(n<0) return 0;
    
    
    uint8_t buffer[DIR_BYTES];
    SerDes::serializeUint8(buffer, input);
    n = (int) send(sockfd, buffer, DIR_BYTES, 0);
    if(n<0) return 0;
    
    return 1;
}

int ClientAPI::sendNameToServer(char * name)
{
    uint8_t h = H_NAME;
    int n = (int) send(sockfd, &h, sizeof(h), 0);
    if(n<0) return -1;
    
    if (strlen(name)>MAX_NAME_LENGTH)
        name[MAX_NAME_LENGTH] = 0;
    
    uint8_t len = strlen(name)+1;
    
    n = (int) send(sockfd, &len, sizeof(len), 0);
    if(n<0) return -1;
    
    n = (int) send(sockfd, name, len, 0);
    if(n<0) return -1;
    
    return 0;
}

int ClientAPI::readWinnerNameFromServer(std::string& winnername)
{
    uint8_t h;
    if(recv(sockfd, &h, sizeof(h), 0)<0)
        return -1;
    
    if (h!=H_NAME)
        return -1;
    
    uint8_t namelen;
    if(recv(sockfd, &namelen, sizeof(namelen), 0)<0)
        return -1;
    
    char name[namelen];
    if(recv(sockfd, &name, namelen, 0)<0)
        return -1;
    
    winnername = name;
    
    return 0;
}

int ClientAPI::readHeaderFromServer(uint8_t& h)
{
    uint8_t buffer[ID_BYTES];
    int n = (int) recv(sockfd, buffer, HEADER_BYTES, 0);
    if(n<0) return -1;
    SerDes::deserializeUint8(buffer, h);
    return 0;
}
