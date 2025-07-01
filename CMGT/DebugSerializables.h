#pragma once
#include "SerializableBehaviour.h"

SerializableObject(NestedDebugObject, SerializableBehaviour)
SerializeFields(debugInt, debugFloat)
int debugInt = 3;
float debugFloat = 4.5;

};

SerializableObject(DebugObject, SerializableBehaviour)
SerializeFields(debugInt, nestedObject)
int debugInt = 3;
NestedDebugObject nestedObject;
};