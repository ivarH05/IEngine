#pragma once

#include "application.h"
#include "Pointer.h"
#include "Scene.h"
#include "Graphics.h"

#include <stdexcept>
#include <vector>

std::vector<Pointer<Object>> Application::_deferredDestructionQueue;
Pointer<Scene> Application::_activeScene;

void Application::Start()
{
    Graphics::Setup();
    while (true)
    {
        _activeScene->run();
    }
}

void Application::DestroyPendingObjects()
{
    for (const Pointer<Object> obj : _deferredDestructionQueue)
        if (obj != nullptr)
            Object::DestroyImmediate(obj);

    _deferredDestructionQueue.clear();
}

void Application::QueueNewDestructable(Pointer<Object> other)
{
    _deferredDestructionQueue.push_back(other);
}