#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "EventHandler.h"
class Event
{
public:
    void addHandler(const EventHandler& handler);
    void removeHandler(const EventHandler& handler);
    void operator()();
    Event& operator+=(const EventHandler& handler);
    Event& operator-=(const EventHandler& handler);

private:
    std::vector<std::unique_ptr<EventHandler>> handlers;

    void notifyHandlers();
};