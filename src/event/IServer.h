#ifndef ISERVER_H
#define ISERVER_H
#include <memory>

#include "ISocket.h"

namespace Event
{
class IServer
{
public:
    virtual void CreateListener(short port) = 0;
    virtual void Close(ISocket* socket) = 0;
};
}
#endif
