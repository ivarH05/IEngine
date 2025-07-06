#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Object.h"
#include "Vector2.h"
#include "Pointer.h"

class Texture2D : public Object
{
private:
    sf::Texture texture;

public:
    Vector2 resolution = Vector2(0, 0);

    static Pointer<Texture2D> LoadStatic(const std::string& path)
    {
        Pointer<Texture2D> result;
        result->LoadTexture(path);

        return result;
    }

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
        resolution = Vector2::Convert(texture.getSize());
    }


    sf::Texture* getTexture()
    {
        return &texture;
    }
};
