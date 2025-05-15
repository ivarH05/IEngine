#pragma once
#include <iostream>
#include "Graphics.h"

namespace IEngine
{
	namespace Core
	{
		class Application
		{
		public:
			static void Start()
			{
				Graphics::Setup();
				while (true)
				{
					
				}
			}
		};
	}
}