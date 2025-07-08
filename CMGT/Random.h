#pragma once
#include <random>
#include "Vector2.h"

class Random
{
public:
    static int Range(int minInclusive, int maxExclusive);

    static float Range(float minInclusive, float maxExclusive);

    static float Next();

    static Vector2 InsideUnitCircle();

private:
    static std::mt19937& GetEngine();
};
