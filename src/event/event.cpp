#include <event2/event.h>
#include <event2/event_struct.h>

#include "event.h"

namespace Event
{
event* Event::GetEvent()
{
    return &m_event;
}
}
