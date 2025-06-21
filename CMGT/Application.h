#pragma once

#include <vector>

template<typename T>
class Pointer;

class Scene;
class Object;

class Application
{
private:
	/// <summary>
	/// List consisting of all objects that should be destroyed at the end of the current frame. 
	/// </summary>
	static std::vector<Pointer<Object>> _deferredDestructionQueue;

	static Scene _activeScene;

	/// <summary>
	/// Actually destroy all objects that have been marked as destroyed
	/// </summary>
	static void DestroyPendingObjects();
	friend class Scene;

public:
	static void Start();

	/// <summary>
	/// Setup a new object ready for destruction after the current frame
	/// </summary>
	static void QueueNewDestructable(Pointer<Object> other);
};