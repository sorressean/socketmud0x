// ****************************************************************************
// SocketMud II Copyright 2004 Brian Graversen
// ****************************************************************************
// Revision History
// ----------------
// 19/01/04) Initial SocketMud II code released
// ****************************************************************************
// This product can be used freely as long as this copyright header remains
// intact. This header may not be removed or changed, and any work released
// based on this code must contain this header information in all files.
// ****************************************************************************

#include <cstdlib>
#include <iostream>
#include "server.h"
#include "socket.h"

static void GameLoop(Server* server)
{
    while(1)
        {
            // poll all sockets for incoming data
            server->PollSockets();

            std::list<Socket*> socketList = server->GetSocketList();

            // echo everything that each socket has sent to us
            for (Socket* sock:socketList)
                {
                    sock->Write(sock->GetInBuffer());
                    sock->ClrInBuffer();
                }

            // flush all outgoing data
            server->FlushSockets();

            // sleep the rest of the pulse
            server->Sleep(5);
        }
}

int main(int argc, char** argv)
{
    Server* server = nullptr;
    int port = 0;

//we check to see if a port was provided.
    if (argc == 2)
        {
            port = atoi(argv[1]);
        }
    else
        {
//todo: allow to change the hard-coded port
            port = 4000;
        }
    if (port < 1024 || port > 9999)
        {
            std::cerr << "Error: Port must be between 1024 and 9999." << std::endl;
            return EXIT_FAILURE;
        }

//create the server and make it listen.
    server = new Server();
    server->Connect(port);

//enter our game loop.
    GameLoop(server);

//nothing happened, exit successfully.
    return 0;
}
