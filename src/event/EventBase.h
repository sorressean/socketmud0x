#ifndef EVENT_BASE_H
#define EVENT_BASE_H
#include <memory>

#include <event2/event.h>

#include "../noncopyable.hpp"

namespace Event
{
/**
* The EventBase is a thin wrapper around libevent's event_base structure.
* This basically exists so that we can manage it under smart pointers
* while still using libevent's create/free mechenism.
*/
class EventBase:public NonCopyable<EventBase>
{
private:
    event_base* m_eventBase;
public:
    EventBase();
    ~EventBase();
    event_base* GetEventBase() const;
    void Dispatch();
    static std::shared_ptr<EventBase> Create();
};

typedef std::shared_ptr<EventBase> EventBasePtr;
}
#endif
