#include <memory>

#include <event2/event_struct.h>
#include <event2/bufferevent.h>

#include "BufferEvent.h"

using namespace std;

namespace Event
{
shared_ptr<BufferEvent> BufferEvent::Create(bufferevent* event)
{
    return make_shared<BufferEvent>(event);
}

BufferEvent::BufferEvent(bufferevent* event):
    m_bufferEvent(event)
{
}

}
