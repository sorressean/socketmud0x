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
#include <memory>

#include "server.h"
#include "socket.h"

using namespace std;

//keeps track if the server is running.
static volatile bool running = false;

static void GameLoop(shared_ptr<Server> server)
{
    while(running)
        {
            // poll all sockets for incoming data
            server->PollSockets();

            auto socketList = server->GetSocketList();

            // echo everything that each socket has sent to us
            for (auto sock:socketList)
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
            cerr << "Error: Port must be between 1024 and 9999." << std::endl;
            return EXIT_FAILURE;
        }

//create the server and make it listen.
    auto server = make_shared<Server>();
    server->Connect(port);

    running = true;
//enter our game loop.
    GameLoop(server);

//nothing happened, exit successfully.
    return EXIT_SUCCESS;
}
