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

#define Script(name, base) \
class name : public base \
{ \
public: \
    void Register(Pointer<ObjectHandler> objectHandler) override \
    { \
        objectHandler->Register<name>(this); \
    } \
    void Unregister(Pointer<ObjectHandler> objectHandler) override \
    { \
        objectHandler->Unregister<name>(this); \
    }


#define OnDestroy() \
    OnFinalizeDestruction() override { \
        OnDestroy(); \
    } \
    void OnDestroy()