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
    // After full update, destroy all objects
    ObjectHandler manager;

    manager.StartAll(); // Should call MyScript::Update()
    manager.FixedUpdateAll(); // Should call MyScript::Update()
    manager.UpdateAll(); // Should call MyScript::Update()
    manager.LateUpdateAll(); // Should call MyScript::Update()
    manager.DrawGizmosAll(); // Should call MyScript::Update()

    Application::DestroyPendingObjects();
}