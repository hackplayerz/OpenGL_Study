#include <iostream>
#include "EventHandler.h"

EventHandler::EventHandler() : id{ 0 } { }
EventHandler::EventHandler(const Func& func) : _func{ func }
{
    id = ++EventHandler::counter;
}

void EventHandler::operator()()
{
    _func();
}

void EventHandler::operator=(const EventHandler& func)
{
    if (_func == nullptr)
    {
        _func = func;
        id = ++EventHandler::counter;
    }
    else
        std::cerr << "¾ÈµÊ" << std::endl;
}

bool EventHandler::operator==(const EventHandler& del)
{
    return id == del.id;
}

bool EventHandler::operator!=(nullptr_t)
{
    return _func != nullptr;
}