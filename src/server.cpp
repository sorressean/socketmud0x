// ****************************************************************************
// SocketMud II Copyright 2004 Brian Graversen
// ****************************************************************************
// Revision History
// ----------------
// 19/01/04) Initial server code released
// ****************************************************************************
// This product can be used freely as long as this copyright header remains
// intact. This header may not be removed or changed, and any work released
// based on this code must contain this header information in all files.
// ****************************************************************************

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include "server.h"

Server::Server()
{

    // initialize control to -1
    control = -1;

    // clear the descriptor sets
    FD_ZERO(&fSet);
    FD_ZERO(&rSet);

    // clear the address buffer
    memset(&my_addr, 0, sizeof(my_addr));

    // initialize lastSleep
    gettimeofday(&lastSleep, NULL);
}

Server::~Server()
{

    // close the connection if it is active
    if (control != -1)
        close(control);
}

bool Server::Connect(int port)
{
    int reuse = 1;

    // try to create a communications endpoint
    if ((control = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return false;

    // set options for this control socket
    if (setsockopt(control, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
        return false;

    // attach the control socket to it's own filedescriptor set
    FD_SET(control, &fSet);

    // settings for this socket, (and set the listning port)
    my_addr.sin_family      = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port        = htons(port);

    // try to bind the mud port
    if (bind(control, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1)
        return false;

    // start listening
    if (listen(control, 3) == -1)
        return false;

    return true;
}

bool Server::PollSockets()
{
    static struct timeval tv;
    Socket* sclose = NULL;
    // copy the permanent descriptor set
    memcpy(&rSet, &fSet, sizeof(fd_set));

    // poll the descriptor set
    if (select(FD_SETSIZE, &rSet, NULL, NULL, &tv) < 0)
        return false;

    // attempt to establish new connections
    Accept();

    // iterate through all sockets and read pending data
    for (Socket* sock: socketList)
        {

            // if previous socket marked for close, then close it
            if (sclose)
            {
                CloseSocket(sclose);
                sclose = NULL; //reset close pointer
            }
            // attempt to read from this socket if pending incoming data
            if (FD_ISSET(sock->GetControl(), &rSet))
                {

                    // if read fails, close the connection, after iterater advances
                    if (sock->Read() == false)
                        sclose = sock;
                }
        }

    return true;
}

void Server::FlushSockets()
{

    // iterate through all sockets and flush outgoing data
    for (Socket* sock: socketList)
        {

            // Attempt to flush this socket, close socket if failure
            if (sock->Flush() == false)
                CloseSocket(sock);
        }
}

// Sleep() should be called with an argument that divided 1000,
// like 4, 5, 8 or 10. This is the amount of "commands" that will
// be processed each second, and it is recommended to have a
// constant defined for this purpose.
void Server::Sleep(int pps)
{
    struct timeval newTime;
    int secs, usecs;

    if (pps <= 0)
        return;

    gettimeofday(&newTime, NULL);

    // calculate exact amount of time we need to sleep
    usecs = (int) (lastSleep.tv_usec -  newTime.tv_usec) + 1000000 / pps;
    secs  = (int) (lastSleep.tv_sec  -  newTime.tv_sec);

    while (usecs < 0)
        {
            usecs += 1000000;
            secs  -= 1;
        }
    while (usecs >= 1000000)
        {
            usecs -= 1000000;
            secs  += 1;
        }

    // sleep if needed
    if (secs > 0 || (secs == 0 && usecs > 0))
        {
            struct timeval sleepTime;

            sleepTime.tv_usec = usecs;
            sleepTime.tv_sec  = secs;

            select(0, NULL, NULL, NULL, &sleepTime);
        }

    // remember when we last slept
    gettimeofday(&lastSleep, NULL);
}

void Server::CloseSocket(Socket *pSocket)
{

    // remove the socket from the socket list
    socketList.remove(pSocket);

    // clear the sockets descriptor from the listening set
    FD_CLR(pSocket->GetControl(), &fSet);

    // and finally delete the socket
    delete pSocket;
}

void Server::Accept()
{
    Socket *pSocket;
    int len = sizeof(my_addr);
    int desc, argp = 1;

    // any new connections pending ?
    if (!FD_ISSET(control, &rSet))
        return;

    // try to accept new connection
    if ((desc = accept(control, (struct sockaddr *) &my_addr, (socklen_t *) &len)) == -1)
        return;

    // allocate a new socket
    pSocket = new Socket(desc);

    // set non-blocking I/O
    ioctl(desc, FIONBIO, &argp);

    // attach to socket list
    socketList.push_back(pSocket);

    // attach to file descriptor set
    FD_SET(desc, &fSet);
}

std::list<Socket*> Server::GetSocketList()
{
    return socketList;
}
