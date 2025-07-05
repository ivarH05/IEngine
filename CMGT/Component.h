#pragma once

#include "Object.h"
#include "ObjectHandler.h"
#include "Pointer.h"
#include "GetSet.h"

class GameObject;
class Transform;

class Component :
	public Object
{
public:
    Component();

    GetSet<Pointer<GameObject>> gameObject;
    GetSet<Pointer<Transform>> transform;
private:
    Pointer<GameObject> _gameObject = nullptr;
    Pointer<Transform> _transform = nullptr;
    virtual void Register(Pointer<ObjectHandler> objectHandler) {};
    virtual void Unregister(Pointer<ObjectHandler> objectHandler) {};
    friend class GameObject;
};

#define Script(name, ...) \
class name : public __VA_ARGS__ \
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