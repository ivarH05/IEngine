#pragma once
#include "Object.h"
namespace IEngine
{
	namespace Core
	{
		class RuntimeObject :
			public Object
		{
		public:
			virtual void Awake() {}
			virtual void Start() {}
			virtual void Update() {}
			virtual void LateUpdate() {}

			virtual void OnEnable() {}
			virtual void OnDisable() {}

			virtual void OnDestroy() {}

			virtual void OnDestroy() {}
			virtual void OnDestroy() {}
		};
	}
}

