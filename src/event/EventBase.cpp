#include <memory>

#include <event2/event.h>

#include "EventBase.h"

namespace Event
{
EventBase::EventBase():
m_eventBase(nullptr)
{
m_eventBase = event_base_new();
}
EventBase::~EventBase()
{
if (m_eventBase != nullptr)
{
event_base_free(m_eventBase);
}
}

event_base* EventBase::GetEventBase() const
{
return m_eventBase;
}

void EventBase::Dispatch()
{
if (m_eventBase != nullptr)
{
event_base_dispatch(m_eventBase);
}
}

EventBasePtr EventBase::Create()
{
return std::make_shared<EventBase>();
}

}
