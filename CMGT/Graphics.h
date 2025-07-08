#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Graphics
{
private:
	static sf::RenderWindow _window;

	static std::vector<sf::Sprite*> _renderQueue;

public:
	static void Render();
	static void QueueForRendering(sf::Sprite* sprite);
};