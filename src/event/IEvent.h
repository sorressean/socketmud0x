#ifndef IEVENT_H
#define IEVENT_H
#include "../noncopyable.hpp"

namespace Event
{
class IEvent:public NonCopyable<IEvent>
{
};
}
#endif
