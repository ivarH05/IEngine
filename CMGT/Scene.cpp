#pragma once

#include "Application.h"
#include "Scene.h"

void Scene::run()
{
    // After full update, destroy all objects
    Application::DestroyPendingObjects();
}