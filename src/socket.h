// ****************************************************************************
// SocketMud II Copyright 2004 Brian Graversen
// ****************************************************************************
// Revision History
// ----------------
// 19/01/04) Initial socket code released
// ****************************************************************************
// This product can be used freely as long as this copyright header remains
// intact. This header may not be removed or changed, and any work released
// based on this code must contain this header information in all files.
// ****************************************************************************

#ifndef HEADER_SOCKET
#define HEADER_SOCKET

// c++ headers
#include <string>

class Socket {
 public:
  Socket  ( int desc );
  ~Socket ( void );

  int                  GetControl     ( void );
  bool                 Read           ( void );
  void                 Write          ( std::string txt );
  bool                 Flush          ( void );
  std::string          GetInBuffer    ( void );
  void                 ClrInBuffer    ( void );

 private:
  int                  control;
  std::string          inBuffer;
  std::string          outBuffer;
};

#endif
