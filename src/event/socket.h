/**
* the event socket is a wrapper around basic socket functions using an event buffer.
*/
#ifndef EVENT_SOCKET_H
#define EVENT_SOCKET_H
#include <optional>
#include <memory>
#include <functional>

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/bufferevent.h>

#include "../noncopyable.hpp"
#include "BufferEvent.h"
#include "event.h"
#include "EventBase.h"
#include "EventCode.h"
#include "IServer.h"
#include "ISocket.h"

namespace Event
{
typedef std::function<void (const EventCode&, int)> SocketAcceptCallback;

class Socket:public ISocket
{
    std::optional<int> m_fd;
    bufferevent * m_eventBuffer;
    SocketAcceptCallback m_acceptCallback;
    EventBasePtr m_eventBase;
    Event m_event;
IServer* m_server;

    void SetNonblocking() const;
    void SetReuseAddress() const;
    virtual void Close();
    void AddListeningEvent();
public:
    Socket(IServer* server, EventBasePtr eventBase);
    ~Socket();
    static std::shared_ptr<Socket> Create(IServer* server, EventBasePtr eventBase);
    static std::shared_ptr<Socket> Create(IServer* server, EventBasePtr eventBase, SocketAcceptCallback acceptCallback);
    virtual void BufferReadEvent(const BufferEvent& event);
    virtual void BufferErrorEvent(const BufferEvent& event, short error);
    virtual void SocketAcceptEvent(const EventCode& event, int fd);
    virtual void InitializeSocket();
    virtual void InitializeSocket(int fd);
    virtual void Listen(int port, int listenQueueLength = 5);
    void SetSocketAcceptCallback(SocketAcceptCallback acceptCallback);
    void SetDescriptor(int fd);
virtual int GetFd() const;
};

typedef std::shared_ptr<Socket> SocketPtr;
}
#endif
