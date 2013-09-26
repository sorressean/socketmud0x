/*
*Socketmud0x
*/
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

#ifndef SOCKET_H
#define SOCKET_H
#include <string>

class Socket
{
    int                  control;
    std::string          inBuffer;
    std::string          outBuffer;
public:
    Socket  ( int desc );
    ~Socket ();

    int                  GetControl     () const;
    bool                 Read           ();
    void                 Write          ( const std::string &txt );
    bool                 Flush          ();
    std::string          GetInBuffer    () const;
    void                 ClrInBuffer    ();
};
#endif
