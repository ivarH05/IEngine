#pragma once

#include "Application.h"
#include "SceneManager.h"
#include "Pointer.h"
#include "Graphics.h"

#include "DebugSerializables.h"
#include <iostream>
#include <sstream>

Scene::Scene() : GameObject(Pointer<ObjectHandler>())
{
    SceneManager::SetActiveScene(Pointer<Scene>(this));
    Pointer<DebugObject> object;

    object->debugInt = 6;
    object->nestedObject.debugFloat = 6.2f;

    std::string serialized = object->Serialize();
    std::cout << serialized << "\n\n";
    auto deserialized = JsonConverter::Deserialize<DebugObject>(serialized);
    std::cout << std::to_string(deserialized.nestedObject.debugFloat);
}

void Scene::run()
{
    SceneManager::SetActiveScene(Pointer<Scene>(this));

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