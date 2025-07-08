#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

class Vector2
{
public:
    float x, y;

    Vector2(float x = 0, float y = 0) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator/(const Vector2& other) const
    {
        return Vector2(x / other.x, y / other.y);
    }

    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    // Compound assignment operators

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(const Vector2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2& operator/=(const Vector2& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const
    {
        return !(*this == other);
    }

    Vector2& operator=(const Vector2& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    static Vector2 Convert(const sf::Vector2i& vector)
    {
        return Vector2(vector.x, vector.y);
    }

    static Vector2 Convert(const sf::Vector2f& vector)
    {
        return Vector2(vector.x, vector.y);
    }

    static Vector2 Convert(const sf::Vector2u& vector)
    {
        return Vector2(static_cast<float>(vector.x), static_cast<float>(vector.y));
    }

    static sf::Vector2f Convert(const Vector2& vector)
    {
        return sf::Vector2f(vector.x, vector.y);
    }

    sf::Vector2f Convert()
    {
        return sf::Vector2f(x, y);
    }

    float Magnitude() const { return std::sqrt(x * x + y * y); }

    float MagnitudeSquared() const
    {
        return x * x + y * y;
    }

    Vector2 Normalized() const
    {
        float mag = Magnitude();
        if (mag == 0) return Vector2(0, 0);
        return *this / mag;
    }

    float Dot(const Vector2& other) const
    {
        return x * other.x + y * other.y;
    }

    float AngleRadians() const
    {
        return std::atan2(y, x);
    }

    float AngleDegrees() const
    {
        return AngleRadians() * (180.0f / 3.14159265358979323846f);
    }

    Vector2 RotatedRadians(float angle) const
    {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        return Vector2(x * cosA - y * sinA, x * sinA + y * cosA);
    }

    Vector2 RotatedDegrees(float angle) const
    {
        return RotatedRadians(angle * (3.14159265358979323846f / 180.0f));
    }

    float Distance(const Vector2& other) const
    {
        return (*this - other).Magnitude();
    }

    float DistanceSquared(const Vector2& other) const
    {
        return (*this - other).MagnitudeSquared();
    }

    std::string ToString()
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

    operator std::string() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};
