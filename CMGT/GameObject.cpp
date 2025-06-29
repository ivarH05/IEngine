#pragma once

#include "GameObject.h"
#include "SceneManager.h"

GameObject::GameObject()
{
	objectHandler = SceneManager::GetActiveObjectHandler();
}

GameObject::GameObject(Pointer<ObjectHandler> handler)
{
	objectHandler = handler;
}