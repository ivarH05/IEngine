#include "Transform.h"
#include "GameObject.h"


Pointer<Transform> Transform::AddChild(Pointer<Transform> newChild) { newChild->SetParent(Pointer<Transform>(this)); return newChild; }
void Transform::RemoveChild(Pointer<Transform> child) { child->ClearParent(); }

void Transform::SetParent(Pointer<Transform> newParent)
{
    ClearParent();
    if (newParent != nullptr)
        newParent->_children.push_back(Pointer(this));
    
    _parent = newParent;
}

void Transform::ClearParent()
{
    if (_parent == nullptr)
        return;

    _parent->_children.erase(
        std::remove_if(_parent->_children.begin(), _parent->_children.end(),
            [this](const Pointer<Transform>& child)
            {
                return child.Get() == this;
            }),
        _parent->_children.end()
    );

    _parent = nullptr;
}



void Transform::RecursiveDirtyFlag(bool pos, bool rot, bool sca)
{
    if (pos)
    {
        getLocalPosition();
        _dfPosition = true;
    }
    if (rot)
    {
        getLocalRotation();
        _dfRotation = true;
    }
    if (sca)
    {
        getLocalScale();
        _dfScale = true;
    }

    for (int i = 0; i < _children.size(); i++)
        _children[i]->RecursiveDirtyFlag(pos, rot, sca);
}

///// position
Vector2 Transform::getPosition()
{
    if (!_dfPosition)
        return _position;
    if (_parent == nullptr)
    {
        _dfPosition = false;
        _position = _localPosition;
        return _localPosition;
    }

    Vector2 parentPos = _parent->getPosition();
    float parentRot = _parent->getRotation();
    Vector2 parentScale = _parent->getScale();

    Vector2 scaledPosition = _localPosition * parentScale;

    Vector2 result = parentPos + scaledPosition.RotatedDegrees(parentRot);

    _position = result;
    _dfPosition = false;

    return result;
}

void Transform::setPosition(Vector2 vec)
{
    _position = vec;
    _dfLocalPosition = true;
    RecursiveDirtyFlag(true, false, false);
    _dfPosition = false;
}

Vector2 Transform::getLocalPosition()
{
    if (!_dfLocalPosition)
        return _localPosition;
    if (_parent == nullptr)
    {
        _dfLocalPosition = false;
        _localPosition = _position;
        return _position;
    }

    Vector2 parentPos = _parent->getPosition();
    float parentRot = _parent->getRotation();
    Vector2 parentScale = _parent->getScale();

    Vector2 result = (_position - parentPos).RotatedDegrees(-parentRot) / parentScale;

    _localPosition = result;
    _dfLocalPosition = false;

    return result;
}

void Transform::setLocalPosition(Vector2 vec)
{
    _localPosition = vec;
    _dfLocalPosition = false;
    RecursiveDirtyFlag(true, false, false);
    _dfPosition = true;
}

///// rotation
float Transform::getRotation()
{
    if (!_dfRotation)
        return _rotation;
    if (_parent == nullptr)
    {
        _dfRotation = false;
        _rotation = _localRotation;
        return _localRotation;
    }

    float result = _parent->getRotation() + _localRotation;

    _rotation = result;
    _dfRotation = false;

    return result;

}

void Transform::setRotation(float value)
{
    _rotation = value;

    _dfLocalRotation = true;
    RecursiveDirtyFlag(true, true, false);
    _dfRotation = false;
}

float Transform::getLocalRotation()
{
    if (!_dfLocalRotation)
        return _localRotation;
    if (_parent == nullptr)
    {
        _dfLocalRotation = false;
        _localRotation = _rotation;
        return _rotation;
    }

    float result = _rotation - _parent->getRotation();

    _localRotation = result;
    _dfLocalRotation = false;

    return result;
}

void Transform::setLocalRotation(float value)
{
    _localRotation = value;

    _dfLocalRotation = false;
    RecursiveDirtyFlag(true, true, false);
    _dfRotation = true;
}

///// scale
Vector2 Transform::getScale()
{
    if (!_dfScale)
        return _scale;
    if (_parent == nullptr)
    {
        _dfScale = false;
        _scale = _localScale;
        return _localScale;
    }

    Vector2 result = _parent->getScale() * _localScale;

    _scale = result;

    _scale = result;
    _dfScale = false;

    return result;
}

void Transform::setScale(Vector2 scale)
{
    _scale = scale;

    _dfLocalScale = true;
    RecursiveDirtyFlag(true, false, true);
    _dfScale = false;
}

Vector2 Transform::getLocalScale()
{
    if (!_dfLocalScale)
        return _localScale;
    if (_parent == nullptr)
    {
        _dfLocalScale = false;
        _localScale = _scale;
        return _scale;
    }

    Vector2 result = _scale / _parent->getScale();

    _scale = result;

    _localScale = result;
    _dfLocalScale = false;

    return result;
}

void Transform::setLocalScale(Vector2 scale)
{
    _localScale = scale;

    _dfLocalScale = false;
    RecursiveDirtyFlag(true, false, true);
    _dfScale = true;
}