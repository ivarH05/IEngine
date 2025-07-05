#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

Component::Component() :
	transform([this]() -> Pointer<Transform> { return _transform; }),
	gameObject([this]() -> Pointer<GameObject> { return _gameObject; })
{

}