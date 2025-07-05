#pragma once
#include "Texture2D.h"
#include "Component.h"
#include "Graphics.h"

Script(SpriteRenderer, Component)
private:
	sf::Sprite _sprite;
	Pointer<Texture2D> _texture = nullptr;
public:

	void Awake() 
	{
		_sprite = sf::Sprite();
	}

	void SetTexture(Pointer<Texture2D> texture)
	{
		_sprite.setTexture(*texture->getTexture());
		_texture = texture;
	}

	void OnRender()
	{
		Graphics::QueueForRendering(&_sprite);
	}
};