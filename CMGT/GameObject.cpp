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
	while (transform->ChildCount() > 0)
		DestroyImmediate(transform->GetChild(0)->gameObject.Get());

	for (int i = 1; i < _components.size(); i++)
	{
		Pointer<Component> component = _components[i];
		if (component == nullptr)
			continue;
		DestroyImmediate(component);
	}

	transform->SetParent(nullptr);
	DestroyImmediate(transform.Get());
}
