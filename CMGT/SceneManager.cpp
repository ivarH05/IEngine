#include "SceneManager.h"
#include "Pointer.h"

Pointer<Scene> SceneManager::_activeScene = Pointer<Scene>(nullptr);

Pointer<Scene> SceneManager::GetActiveScene() 
{ 
	return _activeScene; 
}

void SceneManager::SetActiveScene(Pointer<Scene> scene) 
{ 
	_activeScene = scene; 
}

Pointer<ObjectHandler> SceneManager::GetActiveObjectHandler()
{
	return _activeScene->objectHandler;
}