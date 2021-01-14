#ifndef SERVER_HPP
#define SERVER_HPP
#include <memory>
#include <list>

#include <event2/event.h>

#include "../noncopyable.hpp"
#include "EventBase.h"
#include "EventCode.h"
#include "IServer.h"
#include "ISocket.h"
#include "socket.h"

namespace Event
{
/**
* The server class is responsible for managing listening and connected sockets.
*/
template <typename T>
class Server:public IServer, NonCopyable<Server<T>>
{
    std::list<std::shared_ptr<T>> m_sockets;
    std::shared_ptr<EventBase> m_eventBase;

    void OnAccept(const EventCode& event, int fd)
    {
        auto socket = T::Create(this, m_eventBase);
        socket->InitializeSocket(fd);
        AddSocket(socket);
    }

    void AddSocket(std::shared_ptr<T> socket)
    {
        m_sockets.push_back(socket);
    }

public:
    Server(std::shared_ptr<EventBase> eventBase = nullptr)
    {
        if (eventBase == nullptr)
            {
                m_eventBase = std::make_shared<EventBase>();
            }
        else
            {
                m_eventBase = eventBase;
            }
    }

    ~Server() = default;

    void CreateListener(short port)
    {
        auto socket = Socket::Create(this, m_eventBase, bind(&Server::OnAccept, this, std::placeholders::_1, std::placeholders::_2));
        socket->InitializeSocket();
        socket->Listen(port);
        AddSocket(socket);
    }

    void Close(ISocket* socket)
    {
        const auto socketFd = socket->GetFd();
        const auto itEnd = m_sockets.end();
        for (auto it = m_sockets.begin(); it != itEnd; ++it)
            {
                if ((*it)->GetFd() == socketFd)
                    {
                        m_sockets.erase(it);
                        return;
                    }
            }
    }
};

}
#endif
