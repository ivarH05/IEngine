#pragma once
#include "Scene.h"
#include <stdexcept>
#include <vector>
using namespace IEngine::Core;

void Scene::run()
{
    // Misses functions like updates, rendering etc. 
    throw std::logic_error("Not implemented");

    // After full update, destroy all objects
    DestroyPendingObjects();
}

void Scene::DestroyPendingObjects()
{
    // Destroy the objects one by one, check if the object still exists.
    for (const std::shared_ptr<Object> obj : deferredDestructionQueue)
    {
        if (obj)
            obj->Destroy();
    }

    // Clear list for next frame
    deferredDestructionQueue.clear();
}

void Scene::QueueNewDestructable(std::shared_ptr<Object> other)
{
    deferredDestructionQueue.push_back(other);
}