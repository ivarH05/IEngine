#pragma once

#include "Application.h"
#include "Scene.h"
#include "Pointer.h"

Scene::Scene()
{
    objectHandler = Pointer<ObjectHandler>();
}

void Scene::run()
{
    objectHandler->StartAll();
    objectHandler->FixedUpdateAll();
    objectHandler->UpdateAll();
    objectHandler->LateUpdateAll();
    objectHandler->DrawGizmosAll();

    // After full update, destroy all objects
    Application::DestroyPendingObjects();
}