/**
* Event is a thin wrapper around libevent's struct object.
*/
#ifndef EVENT_H
#define EVENT_H
#include <memory>

#include "../noncopyable.hpp"

#include <event2/event_struct.h>
#include <event2/bufferevent.h>


namespace Event
{
class Event:public NonCopyable<Event>
{
bufferevent* m_event;
public:
Event(bufferevent* event);
static std::shared_ptr<Event> CreateEvent(bufferevent* event);
};

typedef std::shared_ptr<Event> EventPtr;
}
#endif
