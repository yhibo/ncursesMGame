//
//  Client.hpp
//  Server
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#ifndef Client_hpp
#define Client_hpp

#include "../Common/Types.hpp"

class Client{
private:
    uint8_t id;
    int cli_socket;
    sockaddr_in cliAddr;
    std::string name;
public:
    int kills;
    std::thread clith;
    Client(int , sockaddr_in , uint8_t);
    ~Client();
    uint8_t getID();
    int getSocket();
    std::string getName();
    void setName(const char *);
    sockaddr_in getAddr();
};



#endif /* Client_hpp */
