/**
* the event socket is a wrapper around basic socket functions using an event buffer.
*/
#ifndef EVENT_SOCKET_H
#define EVENT_SOCKET_H
#include <memory>

#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/bufferevent.h>

#include "../noncopyable.hpp"
#include "event.h"

namespace Event
{
class Socket:public NonCopyable<Socket>
{
int m_fd;
bufferevent * m_eventBuffer;

Socket();
void SetNonblocking() const;
public:
~Socket();
static std::unique_ptr<Socket> Create();
virtual void BufferReadCallback(EventPtr event);
virtual void BufferErrorCallback(EventPtr event, short error);
};

}
#endif
