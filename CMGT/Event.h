#pragma once

#include <functional>
#include <unordered_map>
#include <algorithm>

template<typename... Args>
class Event
{
public:
    using ListenerID = size_t;
    using Listener = std::function<void(Args...)>;

    ListenerID AddListener(const Listener& listener)
    {
        ListenerID id = nextListenerID++;
        listeners[id] = listener;
        return id;
    }

    void RemoveListener(ListenerID id)
    {
        listeners.erase(id);
    }

    void Invoke(Args... args)
    {
        for (auto& [id, listener] : listeners)
        {
            listener(args...);
        }
    }

private:
    std::unordered_map<ListenerID, Listener> listeners;
    ListenerID nextListenerID = 0;
};
