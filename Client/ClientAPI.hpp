//
//  ClientAPI.hpp
//  Client
//
//  Created by Yhibo Blado Radlovacki Parisi on 14/05/2022.
//

#ifndef ClientAPI_hpp
#define ClientAPI_hpp

#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "../Common/SerDes.hpp"
#include "../Common/Types.hpp"

class ClientAPI
{
private:
    int sockfd;
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
public:
    ~ClientAPI();
    //Initializes the socket
    void init(char* host, char* port);
    void connectToServer();
    int sendInputToServer(uint8_t input);
    int readGameDataFromServer(GameData& gd);
    int readWinnerNameFromServer(std::string &s);
    int readIDFromServer(uint8_t& id);
    int readHeaderFromServer(uint8_t& h);
    int sendNameToServer(char *);

};


#endif /* ClientAPI_hpp */
