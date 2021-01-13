#ifndef BUFFER_EVENT_H
#define BUFFER_EVENT_H
#include <memory>

#include <event2/event_struct.h>
#include <event2/bufferevent.h>

#include "../noncopyable.hpp"

namespace Event
{
/**
* This is a thin wrapper around the libevent bufferevent structure.
*/
class BufferEvent:public NonCopyable<BufferEvent>
{
    bufferevent* m_bufferEvent;
public:
    BufferEvent(bufferevent* event);
    ~BufferEvent() = default;
    static std::shared_ptr<BufferEvent> Create(bufferevent* event);
};

}
#endif
