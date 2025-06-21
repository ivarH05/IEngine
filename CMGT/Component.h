#pragma once

#include "Object.h"
#include "ObjectHandler.h"

class Component :
	public Object
{
private:
    virtual void Register(ObjectHandler* objectHandler) {};
    virtual void Unregister(ObjectHandler* objectHandler) {};
    friend class GameObject;
};

#define DESTRUCTABLE(ComponentType) \
public: \
    void OnFinalizeDestruction() final override { \
        if constexpr (has_OnDestroy<ComponentType>::value) { \
            static_cast<ComponentType*>(this)->OnDestroy(); \
        } \
    } \
    void Register(ObjectHandler* objectHandler) override {\
        objectHandler->Register<ComponentType>(this); \
    }\
    void Unregister(ObjectHandler* objectHandler) override {\
        objectHandler->Unregister<ComponentType>(this); \
    }

