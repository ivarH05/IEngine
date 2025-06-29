#pragma once
#include "Scene.h"
#include "Pointer.h"

static class SceneManager
{
private:
	static Pointer<Scene> _activeScene;
public:
	static Pointer<Scene> GetActiveScene() { return _activeScene; }
	static void SetActiveScene(Pointer<Scene> scene) { _activeScene = scene; }

	static Pointer<ObjectHandler> GetActiveObjectHandler() 
	{
		return _activeScene->objectHandler;
	}
};