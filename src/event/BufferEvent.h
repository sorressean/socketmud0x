/**
* Event is a thin wrapper around libevent's struct object.
*/
#ifndef BUFFER_EVENT_H
#define BUFFER_EVENT_H
#include <memory>

#include <event2/event_struct.h>
#include <event2/bufferevent.h>

#include "IEvent.h"

namespace Event
{
class BufferEvent:public IEvent
{
bufferevent* m_bufferEvent;
public:
BufferEvent(bufferevent* event);
~BufferEvent() = default;
static std::shared_ptr<BufferEvent> Create(bufferevent* event);
};

}
#endif
