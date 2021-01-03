/**
* The EventBase is a thin wrapper around libevent's event_base structure.
*/
#ifndef EVENT_BASE_H
#define EVENT_BASE_H
#include <memory>

#include <event2/event.h>

namespace Event
{
class EventBase
{
private:
event_base* m_eventBase;
