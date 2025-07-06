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
protected:
    Pointer<ObjectHandler> objectHandler;
private:
    void OnFinalizeDestruction() override 
    { 
        Unregister(objectHandler); 
        _transform = nullptr; 
        _gameObject = nullptr;
    }
    Pointer<GameObject> _gameObject = nullptr;
    Pointer<Transform> _transform = nullptr;
    virtual void Register(Pointer<ObjectHandler> objectHandler) { };
    virtual void Unregister(Pointer<ObjectHandler> objectHandler) { };
    friend class GameObject;
};

#define Script(name, ...) \
class name : public __VA_ARGS__ \
{ \
public: \
    void Register(Pointer<ObjectHandler> objectHandler) override \
    { \
        this->objectHandler = objectHandler; \
        objectHandler->Register<name>(this); \
    } \
    void Unregister(Pointer<ObjectHandler> objectHandler) override \
    { \
        objectHandler->Unregister<name>(this); \
    }


#define OnDestroy() \
    OnFinalizeDestruction() override { \
        Unregister(objectHandler); \
        OnDestroy(); \
    } \
    void OnDestroy()