#pragma once
#include "Graphics.h"

sf::RenderWindow Graphics::_window(sf::VideoMode(800, 600), "IEngine"); 
std::vector<sf::Sprite*> Graphics::_renderQueue;

void Graphics::Render()
{
	_window.clear();
	for (int i = 0; i < _renderQueue.size(); i++)
		_window.draw(*_renderQueue[i]);
	_window.display();
	_renderQueue.clear();
}


void Graphics::QueueForRendering(sf::Sprite* sprite)
{
	_renderQueue.push_back(sprite);
}