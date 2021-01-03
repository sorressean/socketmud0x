#include <memory>

#include <event2/event_struct.h>
#include <event2/bufferevent.h>

#include "event.h"

using namespace std;

namespace Event
{
EventPtr Event::CreateEvent(bufferevent* event)
{
return make_shared<Event>(event);
}

Event::Event(bufferevent* event)
{
}

}
