/*
*Socketmud0x
*/
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

#ifndef SERVER_H
#define SERVER_H
#include <list>
#include <memory>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>

#include "socket.h"

class Server
{
    void                 Accept           ();
    void                 CloseSocket      ( std::shared_ptr<Socket> socket);
    std::list<std::shared_ptr<Socket>>   socketList;
    int                  control;
    fd_set               fSet;
    fd_set               rSet;
    sockaddr_in          my_addr;
    struct timeval       lastSleep;
public:
    Server  ();
    ~Server ();

    bool                 Connect          ( int port );
    void                 FlushSockets     ();
    bool                 PollSockets      ();
    void                 Sleep            ( const int pps );
    std::list<std::shared_ptr<Socket>>   GetSocketList    () const;
};
#endif
