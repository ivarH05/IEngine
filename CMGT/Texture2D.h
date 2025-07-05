#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Object.h"

class Texture2D : public Object
{
private:
    sf::Texture texture;

public:
    Texture2D() { }

    Texture2D(const std::string& path)
    {
        if (!texture.loadFromFile(path))
            throw std::runtime_error("Texture was not found");
    }

    void LoadTexture(const std::string& path)
    {
        if (!texture.loadFromFile(path))
            throw std::runtime_error("Texture was not found");
    }

    sf::Texture* getTexture()
    {
        return &texture;
    }
};
