/**
* The event wrapper wraps the event struct from libevent.
*/
#ifndef EVENT_H
#define EVENT_H
#include <event2/event.h>
#include <event2/event_struct.h>

namespace Event
{
#include "../noncopyable.hpp"

class Event:public NonCopyable<Event>
{
    event m_event;
public:
    Event() = default;
    ~Event() = default;
    event* GetEvent();
};
}
#endif
