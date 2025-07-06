#pragma once
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Graphics.h"

void SpriteRenderer::Awake()
{
	_sprite = sf::Sprite();
}

void SpriteRenderer::SetTexture(Pointer<Texture2D> texture, bool centerPivot)
{
	_sprite.setTexture(*texture->getTexture());
	_texture = texture;
	if (centerPivot)
		_sprite.setOrigin(Vector2::Convert(texture->resolution / 2));
}

void SpriteRenderer::OnRender()
{
	_sprite.setPosition(Vector2::Convert(transform->position));
	_sprite.setRotation(transform->rotation);
	_sprite.setScale(Vector2::Convert(transform->scale));
	Graphics::QueueForRendering(&_sprite);
}