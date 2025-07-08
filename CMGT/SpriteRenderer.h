#pragma once
#include "Texture2D.h"
#include "Component.h"

#include "Transform.h"

Script(SpriteRenderer, Component)
private:
	sf::Sprite _sprite;
	Pointer<Texture2D> _texture = nullptr;
public:

	void Awake();

	void SetTexture(Pointer<Texture2D> texture, bool centerPivot = true);

	void OnRender();
};