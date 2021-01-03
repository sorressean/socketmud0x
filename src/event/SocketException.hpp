#ifndef SOCKET_EXCEPTION_HPP
#define SOCKET_EXCEPTION_HPP
#include <stdexcept>

namespace Event
{
class SocketException:public std::runtime_error
{
public:
using std::runtime_error::runtime_error;
};
}
#endif
