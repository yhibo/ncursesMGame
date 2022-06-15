//
//  main.cpp
//  Srvr
//
//  Created by Yhibo Blado Radlovacki Parisi on 23/05/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "Server.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        error("ERROR, no port provided");
    }

    signal(SIGPIPE, SIG_IGN);
    
    srand((unsigned int)time(NULL));

    Server server(atoi(argv[1]));
    server.run();

}
