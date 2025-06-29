#pragma once

#include "application.h"
#include "Scene.h"

std::vector<Pointer<Object>> Application::_deferredDestructionQueue;
Pointer<Scene> Application::_activeScene;

void Application::Start()
{
    while (true)
    {
        _activeScene->run();
    }
}

void Application::DestroyPendingObjects()
{
    for (const Pointer<Object> obj : _deferredDestructionQueue)
    {
        if (obj != nullptr)
            Object::DestroyImmediate(obj);
    }

    _deferredDestructionQueue.clear();
}

void Application::QueueNewDestructable(Pointer<Object> other)
{
    _deferredDestructionQueue.push_back(other);
}