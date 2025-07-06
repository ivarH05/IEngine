#include "Random.h"
#include <cmath>

std::mt19937& Random::GetEngine()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
    return engine;
}

int Random::Range(int minInclusive, int maxExclusive)
{
    std::uniform_int_distribution<int> dist(minInclusive, maxExclusive - 1);
    return dist(GetEngine());
}

float Random::Range(float minInclusive, float maxExclusive)
{
    std::uniform_real_distribution<float> dist(minInclusive, maxExclusive);
    return dist(GetEngine());
}

float Random::Next()
{
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(GetEngine());
}

Vector2 Random::InsideUnitCircle()
{
    float angle = Range(0.0f, 2.0f * 3.14159265f);
    float radius = std::sqrt(Next());  // sqrt to ensure uniform distribution
    return Vector2(std::cos(angle), std::sin(angle)) * radius;
}
