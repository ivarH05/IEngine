#pragma once

#include "Object.h"
#include "Pointer.h"
#include "Application.h"

#include <iostream>

void Object::FinalizeDestruction()
{
    OnFinalizeDestruction();
    if (_controlBlock)
        _controlBlock->OnObjectDestroyed();
}

void Object::CueForDestruction()
{
    Application::QueueNewDestructable(Pointer<Object>(this));
}