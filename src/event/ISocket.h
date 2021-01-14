#ifndef ISOCKET_H
#define ISOCKET_H
#include "../noncopyable.hpp"

namespace Event
{
class ISocket:public NonCopyable<ISocket>
{
virtual void Close() = 0;
public:
virtual void InitializeSocket() = 0;
virtual void InitializeSocket(int fd) = 0;
virtual void Listen(int port, int listenQueueLength = 5) = 0;
virtual int GetFd() const = 0;
};
}
#endif
