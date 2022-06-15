//
//  ServerAPI.hpp
//  Server
//
//  Created by Yhibo Blado Radlovacki Parisi on 25/05/2022.
//

#ifndef ServerAPI_hpp
#define ServerAPI_hpp

#include "../Common/SerDes.hpp"
#include "Client.hpp"
#include <fcntl.h>

class ServerAPI {
private:
public:
    int sendWinnerStatusToClient(Client *);
    int sendLoserStatusToClient(Client *, std::string winnername);
    int sendIdToClient(Client * c);
    int sendGameDataToClient(Client * c, GameData gd);
    int readHeaderFromClient(Client * c, uint8_t& h);
    int getNameFromClient(Client * c);
    int readDirFromClient(Client * c, uint8_t& dir);
    bool setSocketBlockingEnabled(int sockFd, bool blocking);
};

#endif /* ServerAPI_hpp */
