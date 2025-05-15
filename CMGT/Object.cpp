#pragma once
#include "Object.h"
#include "Scene.h"
using namespace IEngine::Core;

Object* Object::operator->()
{
    if (_isDestroyed)
        return nullptr;
    return this;
}


void Object::Destroy()
{
    _isDestroyed = true;
}

void Object::Destroy(std::shared_ptr<Object> other)
{
    scene->QueueNewDestructable(other);
}