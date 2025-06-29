#pragma once

#include "Object.h"
#include "Component.h"
#include <vector>
#include "Pointer.h"
#include "ObjectHandler.h"


class GameObject :
	public Object
{
private:
	std::vector<Pointer<Component>> _components;

	void OnFinalizeDestruction() final override
	{
		for (int i = 0; i < _components.size(); i++)
		{
			Pointer<Component> component = _components[i];

			component->Unregister(objectHandler);
			DestroyImmediate(component);
		}
	}

protected:
	Pointer<ObjectHandler> objectHandler;

public:
	GameObject();
	GameObject(Pointer<ObjectHandler>);

	template<typename T>
	void AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
		Pointer<T> component;
		Pointer<Component> ptr = component.Cast<Component>();
		_components.push_back(ptr);

		component->Register(objectHandler);

		if constexpr (has_Awake<T>::value)
			component
			->Awake();
	}

	template<typename T>
	Pointer<T> GetComponent()
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
	std::vector<Component> GetComponents()
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
};