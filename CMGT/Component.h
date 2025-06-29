#pragma once

#include "Object.h"
#include "ObjectHandler.h"
#include "Pointer.h"

class Component :
	public Object
{
private:
    virtual void Register(Pointer<ObjectHandler> objectHandler) {};
    virtual void Unregister(Pointer<ObjectHandler> objectHandler) {};
    friend class GameObject;
};

#define DESTRUCTABLE(ComponentType) \
public: \
    void OnFinalizeDestruction() final override { \
        if constexpr (has_OnDestroy<ComponentType>::value) { \
            static_cast<ComponentType*>(this)->OnDestroy(); \
        } \
    } \
    void Register(Pointer<ObjectHandler> objectHandler) override {\
        objectHandler->Register<ComponentType>(this); \
    }\
    void Unregister(Pointer<ObjectHandler> objectHandler) override {\
        objectHandler->Unregister<ComponentType>(this); \
    }

