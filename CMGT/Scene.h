#pragma once
#include "Object.h"
#include <vector>
#include <memory>

namespace IEngine
{
	namespace Core
	{
		class Scene : public Object
		{
		public:
			/// <summary>
			/// Scene contains the main loop of the engine. run will update, render, clean up, etc. 
			/// </summary>
			void run();
			/// <summary>
			/// Setup a new object ready for destruction after the current frame
			/// </summary>
			void QueueNewDestructable(std::shared_ptr<Object> other);

		private:
			/// <summary>
			/// List consisting of all objects that should be destroyed at the end of the current frame. 
			/// </summary>
			std::vector<std::shared_ptr<Object>> deferredDestructionQueue;

			/// <summary>
			/// Actually destroy all objects that have been marked as destroyed
			/// </summary>
			void DestroyPendingObjects();
		};
	}
}

