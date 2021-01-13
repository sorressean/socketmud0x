#include <memory>

#include "event/server.h"

using namespace std;

int main(int argc, const char** argv)
{
//event base manages and controls all events.
    auto eventBase = Event::EventBase::Create();
    auto server = Event::Server(eventBase);
    server.CreateListener(4000);
    eventBase->Dispatch();
    return 0;
}
