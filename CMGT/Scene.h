#pragma once

#include "Object.h"

class Scene : public Object
{
private:

public:
	/// <summary>
	/// Scene contains the main loop of the engine. run will update, render, clean up, etc. 
	/// </summary>
	void run();
};

