#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

Component::Component() :
	transform([this]() -> Pointer<Transform> { return _transform; }),
	gameObject([this]() -> Pointer<GameObject> { return _gameObject; })
{

}

void Component::OnFinalizeDestruction()
{
    if (_gameObject != nullptr)
        _gameObject->RemoveComponent<Component>(Pointer(this));

    if (objectHandler != nullptr)
        Unregister(objectHandler);
    _transform = nullptr;
    _gameObject = nullptr;
}