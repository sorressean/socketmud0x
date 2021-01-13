#ifndef EVENT_CODE_H
#define EVENT_CODE_H
#include <memory>

#include <event2/bufferevent.h>

#include "../noncopyable.hpp"

namespace Event
{
class EventCode:public NonCopyable<EventCode>
{
short m_event;
public:
EventCode(short event);
~EventCode() = default;
};
}
#endif
