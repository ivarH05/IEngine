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

protected:
	Pointer<ObjectHandler> handler;

public:
	template<typename T>
	void AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
		Component component = Pointer<Component>;
		_components.push_back(component);
	}

	template<typename T>
	Component GetComponent()
	{
		for (int i = 0; i < _components.size; i++)
		{
			Pointer<Component> c = _components[i];
			T* casted = dynamic_cast<T*>(c.Get());
			if (casted != nullptr)
				return casted;
		}
		return nullptr;
	}

	template<typename T>
	std::vector<Component> GetComponents()
	{
		std::vector<Component> result = new std::vector<Component>();
		for (int i = 0; i < _components.size; i++)
		{
			Pointer<Component> c = _components[i];
			T* casted = dynamic_cast<T*>(c.Get());
			if (casted != nullptr)
				result.push_back(c);
		}
		return result;
	}
};