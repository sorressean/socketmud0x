/**
* A server is responsible for managing and handling multiple connections.
*/
#ifndef SERVER_H
#define SERVER_H
#include <memory>
#include <list>

#include <event2/event.h>

#include "../noncopyable.hpp"
#include "EventBase.h"
#include "EventCode.h"
#include "socket.h"

namespace Event
{
/**
* The server class is responsible for managing listening and connected sockets.
*/
class Server:public NonCopyable<Server>
{
    std::list<SocketPtr> m_sockets;
    std::shared_ptr<EventBase> m_eventBase;

    void OnAccept(const EventCode& event, int fd);
    void AddSocket(SocketPtr socket);
public:
    Server(std::shared_ptr<EventBase> eventBase = nullptr);
    ~Server() = default;
    void CreateListener(short port);
};

}
#endif
