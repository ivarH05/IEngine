#pragma once

#include "Application.h"
#include "Scene.h"
#include "Pointer.h"

Scene::Scene()
{
    handler = Pointer<ObjectHandler>();
}

void Scene::run()
{
    handler->StartAll();
    handler->FixedUpdateAll();
    handler->UpdateAll();
    handler->LateUpdateAll();
    handler->DrawGizmosAll();

    // After full update, destroy all objects
    Application::DestroyPendingObjects();
}