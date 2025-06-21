// update/UpdateManager.cpp
#include "ObjectHandler.h"

void ObjectHandler::StartAll()
{
    for (auto& f : startMethods) f();
}

void ObjectHandler::FixedUpdateAll()
{
    for (auto& f : fixedUpdateMethods) f();
}

void ObjectHandler::UpdateAll()
{
    for (auto& f : updateMethods) f();
}

void ObjectHandler::LateUpdateAll()
{
    for (auto& f : lateUpdateMethods) f();
}

void ObjectHandler::DrawGizmosAll()
{
    for (auto& f : drawGizmosMethods) f();
}
