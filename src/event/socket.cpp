#include <memory>

#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <string>

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/bufferevent.h>

#include "event.h"
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
static void BufferReadCallback(bufferevent* event, void *arg)
{
Socket* socket = static_cast<Socket*>(arg);
auto eventObject = Event::CreateEvent(event);
socket->BufferReadCallback(eventObject);
}
static void BufferErrorCallback(bufferevent* event, short error, void *arg)
{
Socket* socket = static_cast<Socket*>(arg);
auto eventObject = Event::CreateEvent(event);
socket->BufferErrorCallback(eventObject, error);
}


Socket::Socket():
m_fd(0),
m_eventBuffer(nullptr)
{
}

Socket::~Socket()
{
}

void Socket::SetNonblocking() const
{
int flags = fcntl(m_fd, F_GETFL);

if (flags < 0)
{
const int error = errno;
throw SocketException("Socket failed to set nonblocking, could not fetch file status flags: "+string(strerror(error)));
}

flags |= O_NONBLOCK;
const int result = fcntl(m_fd, F_SETFL, flags);
if (result == -1)
{
const int error = errno;
throw SocketException("Socket failed to set nonblocking, could not set file status flags: " + string(strerror(error)));
}
}

void Socket::BufferReadCallback(EventPtr event)
{
}
void Socket::BufferErrorCallback(EventPtr event, short error)
{
}

}
