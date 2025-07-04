#pragma once

#include "Object.h"
#include "Component.h"
#include "Pointer.h"
#include "ObjectHandler.h"
#include <vector>

class GameObject :
	public Object
{
private:
	std::vector<Pointer<Component>> _components;
	void OnFinalizeDestruction() final override;

protected:
	Pointer<ObjectHandler> objectHandler;

public:
	GameObject();
	GameObject(Pointer<ObjectHandler>);

	template<typename T>
	Pointer<T> AddComponent();

	template<typename T>
	Pointer<T> GetComponent();

	template<typename T>
	std::vector<Component> GetComponents();
};

template<typename T>
Pointer<T> GameObject::AddComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
	Pointer<T> component;
	Pointer<Component> ptr = component.Cast<Component>();
	_components.push_back(ptr);

	component->Register(objectHandler);

	if constexpr (has_Awake<T>::value)
		component
		->Awake();
	return component;
}

template<typename T>
Pointer<T> GameObject::GetComponent()
{
	for (int i = 0; i < _components.size(); i++)
	{
		Pointer<Component> c = _components[i];
		T* casted = dynamic_cast<T*>(c.Get());
		if (casted != nullptr)
			return Pointer<T>(casted);
	}
	return nullptr;
}

template<typename T>
std::vector<Component> GameObject::GetComponents()
{
	std::vector<Component> result = new std::vector<Component>();
	for (int i = 0; i < _components.size(); i++)
	{
		Pointer<Component> c = _components[i];
		T* casted = dynamic_cast<T*>(c.Get());
		if (casted != nullptr)
			result.push_back(c);
	}
	return result;
}