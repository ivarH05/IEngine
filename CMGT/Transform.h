#pragma once

#include "Component.h"
#include "Vector2.h"
#include "GetSet.h"

#include <vector>

Script(Transform, Component)

private:
	// relations

	std::vector<Pointer<Transform>> _children = std::vector<Pointer<Transform>>();

	// Transformations
	Pointer<Transform> _parent = nullptr;

	Vector2 _position = Vector2(0, 0);
	float _rotation = 0;
	Vector2 _scale = Vector2(1, 1);

	Vector2 _localPosition = Vector2(0, 0);
	float _localRotation = 0;
	Vector2 _localScale = Vector2(1, 1);

	// Dirty flags

	bool _dfPosition = true;
	bool _dfRotation = true;
	bool _dfScale = true;

	bool _dfLocalPosition = false;
	bool _dfLocalRotation = false;
	bool _dfLocalScale = false;

public:

	GetSet<Vector2> position;
	GetSet<float> rotation;
	GetSet<Vector2> scale;

	GetSet<Vector2> localPosition;
	GetSet<float> localRotation;
	GetSet<Vector2> localScale;

	Transform() :
		position(		[this](){ return getPosition(); },		[this](const Vector2& vec) { setPosition(vec); }),
		rotation(		[this](){ return getRotation(); },		[this](float rot) { setRotation(rot); }),
		scale(			[this](){ return getScale(); },			[this](const Vector2& scale) { setScale(scale); }),
		localPosition(	[this](){ return getLocalPosition(); }, [this](const Vector2& vec) { setLocalPosition(vec); }),
		localRotation(	[this](){ return getLocalRotation(); }, [this](float rot) { setLocalRotation(rot); }),
		localScale(		[this](){ return getLocalScale(); },	[this](const Vector2& scale) { setLocalScale(scale); }) 
	{ }

	Pointer<Transform> AddChild(Pointer<Transform> newChild);
	void RemoveChild(Pointer<Transform> child);

	Pointer<Transform> GetParent() { return _parent; }

private:

	// Helper methods

	void RecursiveDirtyFlag(bool pos, bool rot, bool sca);

	void SetParent(Pointer<Transform> newParent);

	void ClearParent();

	// Getters and Setters

	Vector2 getPosition();
	float getRotation();
	Vector2 getScale();

	Vector2 getLocalPosition();
	float getLocalRotation();
	Vector2 getLocalScale();

	void setPosition(Vector2 vec);
	void setRotation(float value);
	void setScale(Vector2 scale);

	void setLocalPosition(Vector2 vec);
	void setLocalRotation(float value);
	void setLocalScale(Vector2 scale);
};