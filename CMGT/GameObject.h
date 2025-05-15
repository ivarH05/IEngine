#pragma once
#include "Object.h"
#include "Component.h"
#include <vector>
#include <memory>

namespace IEngine
{
	namespace Core
	{
		class GameObject :
			public Object
		{
		public:
			template<typename T>
			void AddComponent()
			{
				static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
				Component component = std::shared_ptr<Component>;
				_components.push_back(component);
			}

			template<typename T>
			Component GetComponent()
			{
				for (int i = 0; i < _components.size; i++)
				{
					std::shared_ptr<Component> c = _components[i];
					T* casted = dynamic_cast<T*>(c.get());
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
					std::shared_ptr<Component> c = _components[i];
					T* casted = dynamic_cast<T*>(c.get());
					if (casted != nullptr)
						result.push_back(c);
				}
				return result;
			}
			
		private:
			std::vector<std::shared_ptr<Component>> _components;
		};
	}
}

