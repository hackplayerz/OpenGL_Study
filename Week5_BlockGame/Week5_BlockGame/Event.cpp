#include "Event.h"

void Event::addHandler(const EventHandler& handler)
{
    handlers.push_back(std::unique_ptr<EventHandler>(new EventHandler{ handler }));
}

void Event::removeHandler(const EventHandler& handler)
{
    for (std::vector<std::unique_ptr<EventHandler>>::iterator to_remove = handlers.begin();
        to_remove != handlers.end();
        ++to_remove)
    {
        if (*(*to_remove) == handler)
        {
            handlers.erase(to_remove);
            break;
        }
    }
}

void Event::operator()()
{
    notifyHandlers();
}

Event& Event::operator+=(const EventHandler& handler)
{
    addHandler(handler);

    return *this;
}

Event& Event::operator-=(const EventHandler& handler)
{
    removeHandler(handler);

    return *this;
}

void Event::notifyHandlers()
{
    for (std::vector<std::unique_ptr<EventHandler>>::iterator func = handlers.begin();
        func != handlers.end();
        ++func)
    {
        if (*func != nullptr)
            (*(*func))();
    }
}