#pragma once

#include "Application.h"
#include "SceneManager.h"
#include "Pointer.h"

Scene::Scene() : GameObject(Pointer<ObjectHandler>())
{

}

void Scene::run()
{
    SceneManager::SetActiveScene(Pointer<Scene>(this));

    objectHandler->StartAll();
    objectHandler->FixedUpdateAll();
    objectHandler->UpdateAll();
    objectHandler->LateUpdateAll();
    objectHandler->DrawGizmosAll();

    // After full update, destroy all objects
    Application::DestroyPendingObjects();
}