#pragma once

#include "Pointer.h"
#include "Application.h"

void Object::Destroy()
{
    OnDestroy();

    if (_controlBlock)
        _controlBlock->OnObjectDestroyed();

    delete this;
}

void Object::Destroy(Pointer<Object> other)
{
    Application::QueueNewDestructable(other);
}