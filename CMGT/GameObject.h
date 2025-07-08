#pragma once

#include "Object.h"
#include "Component.h"
#include "Pointer.h"
#include "GetSet.h"
#include "ObjectHandler.h"
#include <vector>

class Transform;

class GameObject :
	public Object
{
private:
	std::vector<Pointer<Component>> _components;
	void OnFinalizeDestruction() final override;
	void Setup();

	template<typename T>
	void RemoveComponent(Pointer<T> component);

	friend class Component;

protected:
	Pointer<ObjectHandler> objectHandler = nullptr;
	Pointer<Transform> _transform = nullptr;

public:
	GameObject();
	GameObject(Pointer<ObjectHandler>);
	GetSet<Pointer<Transform>> transform;

	template<typename T>
	Pointer<T> AddComponent();

	template<typename T>
	Pointer<T> GetComponent();

	template<typename T>
	std::vector<Component> GetComponents();
};

template<typename T>
void GameObject::RemoveComponent(Pointer<T> component)
{
	static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
	for (auto it = _components.begin(); it != _components.end(); ++it)
	{
		if (*it != component)
			continue;

		_components.erase(it);
		break;
	}
}


template<typename T>
Pointer<T> GameObject::AddComponent()
{
	static_assert(!std::is_abstract<T>::value, "Type cannot be abstract");
	static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
	Pointer<T> component;
	Pointer<Component> ptr = component.Cast<Component>();

	ptr->_gameObject = Pointer<GameObject>(this);
	ptr->_transform = transform;

	_components.push_back(ptr);

	component->Register(objectHandler);

	if constexpr (has_Awake<T>::value)
		component->Awake();

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
	std::vector<Component> result = std::vector<Component>();
	for (int i = 0; i < _components.size(); i++)
	{
		Pointer<Component> c = _components[i];
		T* casted = dynamic_cast<T*>(c.Get());
		if (casted != nullptr)
			result.push_back(c);
	}
	return result;
}