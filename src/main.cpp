#include <memory>

#include "event/server.hpp"

using namespace std;

int main(int argc, const char** argv)
{
//event base manages and controls all events.
    auto eventBase = Event::EventBase::Create();
    auto server = Event::Server<Event::Socket>(eventBase);
    server.CreateListener(4000);
    eventBase->Dispatch();
    return 0;
}
