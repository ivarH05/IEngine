#pragma once

#include "Object.h"
#include "Pointer.h"
#include "Application.h"

void Object::FinalizeDestruction()
{
    OnFinalizeDestruction();
}

void Object::CueForDestruction()
{
    Application::QueueNewDestructable(Pointer<Object>(this));
}

Object::~Object()
{
    if (_controlBlock != nullptr)
        _controlBlock->OnObjectDestroyed();
}