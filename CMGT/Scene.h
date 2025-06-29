#pragma once

#include "GameObject.h"

class Scene : public GameObject
{
private:
	friend class SceneManager;

public:
	/// <summary>
	/// Scene contains the main loop of the engine. run will update, render, clean up, etc. 
	/// </summary>
	void run();

	Scene();
};

