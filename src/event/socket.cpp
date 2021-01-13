#include <functional>
#include <memory>
#include <optional>
#include <string>

#include <fcntl.h>
#include <unistd.h>

#include <errno.h>
#include <cstring>

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/bufferevent.h>

#include "event.h"
#include "BufferEvent.h"
#include "EventBase.h"
#include "EventCode.h"
#include "socket.h"
#include "SocketException.hpp"

using namespace std;

extern int errno;

namespace Event
{
/**
* the following functions are defined as callbacks to libevent.
* We will proxy all of our calls to the socket itself.
* These functions simply exist as an adapter from c to c++ classes.
*/
static void BufferReadCallbackProxy(bufferevent* event, void *arg)
{
    Socket* socket = static_cast<Socket*>(arg);
    const auto eventObject = BufferEvent(event);
    socket->BufferReadEvent(eventObject);
}
static void BufferErrorCallbackProxy(bufferevent* event, short error, void *arg)
{
    Socket* socket = static_cast<Socket*>(arg);
    const auto eventObject = BufferEvent(event);
    socket->BufferErrorEvent(eventObject, error);
}
static void SocketAcceptCallbackProxy(int fd, short event, void* arg)
{
    Socket* socket = static_cast<Socket*>(arg);
    const auto eventObject = EventCode(event);
    socket->SocketAcceptEvent(eventObject, fd);
}

SocketPtr Socket::Create(EventBasePtr eventBase)
{
    return make_shared<Socket>(eventBase);
}
SocketPtr Socket::Create(EventBasePtr eventBase, SocketAcceptCallback acceptCallback)
{
    auto socket = make_shared<Socket>(eventBase);
    socket->SetSocketAcceptCallback(acceptCallback);
    return socket;
}

Socket::Socket(EventBasePtr eventBase):
    m_fd(nullopt),
    m_eventBase(eventBase),
    m_eventBuffer(nullptr)
{
}

Socket::~Socket()
{
    Close();
}

void Socket::SetNonblocking() const
{
    if (!m_fd.has_value())
        {
            throw SocketException("Unable to set nonblocking on uninitialized socket.");
        }

    int flags = fcntl(*m_fd, F_GETFL);

    if (flags < 0)
        {
            const int error = errno;
            throw SocketException("Socket failed to set nonblocking, could not fetch file status flags: "+string(strerror(error)));
        }

    flags |= O_NONBLOCK;
    const int result = fcntl(*m_fd, F_SETFL, flags);
    if (result == -1)
        {
            const int error = errno;
            throw SocketException("Socket failed to set nonblocking, could not set file status flags: " + string(strerror(error)));
        }
}

void Socket::SetReuseAddress() const
{
    if (!m_fd.has_value())
        {
            throw SocketException("Unable to set reuse address on uninitialized socket.");
        }

    const int value = 1;
    setsockopt(*m_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
}

void Socket::Close()
{
    if (m_fd.has_value())
        {
            close(*m_fd);
            m_fd = nullopt;
        }
}

void Socket::AddListeningEvent()
{
    if (!m_fd.has_value())
        {
            throw SocketException("Unable to create listening event on uninitialized socket.");
        }

    event_assign(m_event.GetEvent(), m_eventBase->GetEventBase(), *m_fd, EV_READ|EV_PERSIST, SocketAcceptCallbackProxy, nullptr);
    event_add(m_event.GetEvent(), nullptr);
}

void Socket::BufferReadEvent(const BufferEvent& event)
{
}
void Socket::BufferErrorEvent(const BufferEvent& event, short error)
{
}
void Socket::SocketAcceptEvent(const EventCode& event, int fd)
{
    m_acceptCallback(event, fd);
}

void Socket::InitializeSocket()
{
    const int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        {
            const int error = errno;
            throw SocketException("Socket failed to set nonblocking, could not set file status flags: " + string(strerror(error)));
        }
    m_fd = fd;
}

void Socket::InitializeSocket(int fd)
{
    m_fd = fd;
    SetNonblocking();
}

void Socket::Listen(int port, int listenQueueLength)
{
    if (!m_fd.has_value())
        {
            throw SocketException("Listen called without an initialized or valid socket.");
        }

    sockaddr_in listenAddress;
    memset(&listenAddress, 0, sizeof(listenAddress));

    listenAddress.sin_family = AF_INET;
    listenAddress.sin_addr.s_addr = INADDR_ANY;
    listenAddress.sin_port = htons(port);
    int result = bind(*m_fd, (sockaddr*)&listenAddress, sizeof(listenAddress));
    if (result < 0)
        {
            const int error = errno;
            throw SocketException("Socket failed bind: "+string(strerror(error)));
        }

    result = listen(*m_fd, listenQueueLength);
    if (result < 0)
        {
            const int error = errno;
            throw SocketException("Socket failed listen: "+string(strerror(error)));
        }

//set socket options.
    SetReuseAddress();
    SetNonblocking();
    AddListeningEvent();
}

void Socket::SetSocketAcceptCallback(SocketAcceptCallback acceptCallback)
{
    m_acceptCallback = acceptCallback;
}
void Socket::SetDescriptor(int fd)
{
    if (m_fd.has_value())
        {
            Close();
        }
    m_fd = fd;
}

}
