#pragma once
#include <functional>
class EventHandler
{
public:
    using Func = std::function<void()>;

private:
    Func _func;

public:
    int id;
    static int counter;

    EventHandler();
    EventHandler(const Func& func);
    void operator()();
    void operator=(const EventHandler& func);
    bool operator==(const EventHandler& del);
    bool operator!=(nullptr_t);
};

