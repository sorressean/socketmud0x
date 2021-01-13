#include <functional>
#include <memory>
#include <list>

#include "EventBase.h"
#include "server.h"
#include "socket.h"

using namespace std;

namespace Event
{
void Server::OnAccept(const EventCode& event, int fd)
{
auto socket = Socket::Create(m_eventBase);
socket->InitializeSocket(fd);
AddSocket(socket);
}

void Server::AddSocket(SocketPtr socket)
{
m_sockets.push_back(socket);
}

Server::Server(EventBasePtr eventBase)
{
if (eventBase == nullptr)
{
m_eventBase = make_shared<EventBase>();
}
else
{
m_eventBase = eventBase;
}
}

void Server::CreateListener(short port)
{
auto socket = Socket::Create(m_eventBase, bind(&Server::OnAccept, this, placeholders::_1, placeholders::_2));
socket->InitializeSocket();
socket->Listen(port);
AddSocket(socket);
}

}
