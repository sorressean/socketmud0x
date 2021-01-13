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
#include "event.h"
#include "EventBase.h"
#include "EventCode.h"
#include "BufferEvent.h"

namespace Event
{
typedef std::function<void (const EventCode&, int)> SocketAcceptCallback;

class Socket:public NonCopyable<Socket>
{
    std::optional<int> m_fd;
    bufferevent * m_eventBuffer;
    SocketAcceptCallback m_acceptCallback;
    EventBasePtr m_eventBase;
    Event m_event;

    void SetNonblocking() const;
    void SetReuseAddress() const;
    void Close();
    void AddListeningEvent();
public:
    Socket(EventBasePtr eventBase);
    ~Socket();
    static std::shared_ptr<Socket> Create(EventBasePtr eventBase);
    static std::shared_ptr<Socket> Create(EventBasePtr eventBase, SocketAcceptCallback acceptCallback);
    virtual void BufferReadEvent(const BufferEvent& event);
    virtual void BufferErrorEvent(const BufferEvent& event, short error);
    virtual void SocketAcceptEvent(const EventCode& event, int fd);
    void InitializeSocket();
    void InitializeSocket(int fd);
    void Listen(int port, int listenQueueLength = 5);
    void SetSocketAcceptCallback(SocketAcceptCallback acceptCallback);
    void SetDescriptor(int fd);
};

typedef std::shared_ptr<Socket> SocketPtr;
}
#endif
