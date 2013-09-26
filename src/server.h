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

#ifndef HEADER_SERVER
#define HEADER_SERVER

// c++ headers
#include <list>

// c headers
#include <arpa/inet.h>

// local headers
#include "socket.h"

class Server {
 public:
  Server  ( void );
  ~Server ( void );

  bool                 Connect          ( int port );
  void                 FlushSockets     ( void );
  bool                 PollSockets      ( void );
  void                 Sleep            ( int pps );
  std::list<Socket*>   GetSocketList    ( void );

 private:
  void                 Accept           ( void );
  void                 CloseSocket      ( Socket *pSocket );

  std::list<Socket*>   socketList;
  int                  control;
  fd_set               fSet;
  fd_set               rSet;
  sockaddr_in          my_addr;
  struct timeval       lastSleep;
};

#endif
