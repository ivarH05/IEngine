#pragma once

#include <functional>
#include <vector>
#include <algorithm>

template<typename... Args>
class Event
{
public:
    using Listener = std::function<void(Args...)>;

    void AddListener(const Listener& listener)
    {
        listeners.push_back(listener);
    }

    void RemoveListener(const Listener& listener)
    {
        auto it = std::remove_if(listeners.begin(), listeners.end(),
            [&](const Listener& l)  {  return CompareFunctions(l, listener); });
        listeners.erase(it, listeners.end());
    }

    void Invoke(Args... args)
    {
        for (auto& listener : listeners)
        {
            listener(args...);
        }
    }

private:
    std::vector<Listener> listeners;

    static bool CompareFunctions(const Listener& listernerA, const Listener& listenerB)
    {
        if(listernerA.target_type() == listenerB.target_type() &&
            listernerA.template target<void(*)(Args...)>() == listenerB.template target<void(*)(Args...)>())

        return listernerA.target_type() == listenerB.target_type() &&
            listernerA.template target<void(*)(Args...)>() == listenerB.template target<void(*)(Args...)>();
    }
};
