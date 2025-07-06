#pragma once

#include "Application.h"
#include "SceneManager.h"
#include "Pointer.h"
#include "Graphics.h"
#include "Time.h"

Scene::Scene() : GameObject(Pointer<ObjectHandler>())
{
    SceneManager::SetActiveScene(Pointer<Scene>(this));
}

void Scene::run()
{
    SceneManager::SetActiveScene(Pointer<Scene>(this));

    Time::Update();

    objectHandler->StartAll();
    objectHandler->FixedUpdateAll();
    objectHandler->UpdateAll();
    objectHandler->LateUpdateAll();
    objectHandler->RenderAll();
    objectHandler->DrawGizmosAll();

    Graphics::Render();

    // After full update, destroy all objects
    Application::DestroyPendingObjects();
}