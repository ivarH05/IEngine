#pragma once
#include "Scene.h"

template<typename T>
class Pointer;

class SceneManager
{
private:
	static Pointer<Scene> _activeScene;
public:
	static void SetActiveScene(Pointer<Scene> scene);
	static Pointer<Scene> GetActiveScene();
	static Pointer<ObjectHandler> GetActiveObjectHandler();
};