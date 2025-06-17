#pragma once

#include "Object.h"

class RuntimeObject :
	public Object
{
public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}

	virtual void Fixedupdate() {}

	virtual void OnEnable() {}
	virtual void OnDisable() {}
};

