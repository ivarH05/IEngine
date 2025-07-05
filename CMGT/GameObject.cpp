#pragma once

#include "GameObject.h"
#include "SceneManager.h"
#include "Transform.h"


GameObject::GameObject() :
	transform([this]() -> Pointer<Transform> { return _transform; })
{
	objectHandler = SceneManager::GetActiveObjectHandler();
	Setup();
}

GameObject::GameObject(Pointer<ObjectHandler> handler) :
	transform([this]() -> Pointer<Transform> { return _transform; })
{
	objectHandler = handler;
	Setup();
}

void GameObject::Setup()
{
	Pointer<Scene> activeScene = SceneManager::GetActiveScene();
	_transform = AddComponent<Transform>();

	if (!activeScene)
		return;

	if (activeScene->transform == _transform)
		return;

	activeScene->transform->AddChild(_transform);
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
