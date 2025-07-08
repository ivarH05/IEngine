#include "ObjectHandler.h"

void ObjectHandler::StartAll()
{
    onStart.Invoke();
    onStart = Event<>();
}

void ObjectHandler::FixedUpdateAll()
{
    onFixedUpdate.Invoke();
}

void ObjectHandler::UpdateAll()
{
    onUpdate.Invoke();
}

void ObjectHandler::LateUpdateAll()
{
    onLateUpdate.Invoke();
}

void ObjectHandler::RenderAll()
{
    onRender.Invoke();
}

void ObjectHandler::DrawGizmosAll()
{
    onDrawGizmos.Invoke();
}
