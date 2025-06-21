#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Graphics
{
private:
	static sf::Window _window;
public:
	static void Setup()
	{
		static sf::RenderWindow _window(sf::VideoMode(800, 600), "IEngine");
	}
};