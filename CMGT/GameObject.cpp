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

void GameObject::OnFinalizeDestruction()
{
	for (int i = 0; i < _components.size(); i++)
	{
		Pointer<Component> component = _components[i];
		if (component == nullptr)
			continue;
		component->Unregister(objectHandler);
		DestroyImmediate(component);
	}
}