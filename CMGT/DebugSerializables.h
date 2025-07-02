#pragma once
#include "SerializableBehaviour.h"

class NestedDebugObject : public SerializableBehaviour 
{
	SerializeFields(debugInt, debugFloat)
public:
	int debugInt = 3;
	float debugFloat = 4.5;

};

class DebugObject : public SerializableBehaviour 
{
	SerializeFields(debugInt, nestedObject)
public:
	int debugInt = 3;
	NestedDebugObject nestedObject;
};