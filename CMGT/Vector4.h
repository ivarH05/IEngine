#pragma once
#include <string>
#include "Mathf.h"

class Vector4
{
public:
    float x, y, z, w;

    static const Vector4 Zero;
    static const Vector4 One;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0)
        : x(x), y(y), z(z), w(w)
    {
    }

    Vector4 operator+(const Vector4& other) const
    {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 operator-(const Vector4& other) const
    {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 operator*(const Vector4& other) const
    {
        return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    Vector4 operator/(const Vector4& other) const
    {
        return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    Vector4 operator*(float scalar) const
    {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Vector4 operator/(float scalar) const
    {
        return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    Vector4& operator+=(const Vector4& other)
    {
        x += other.x; y += other.y; z += other.z; w += other.w;
        return *this;
    }

    Vector4& operator-=(const Vector4& other)
    {
        x -= other.x; y -= other.y; z -= other.z; w -= other.w;
        return *this;
    }

    Vector4& operator*=(const Vector4& other)
    {
        x *= other.x; y *= other.y; z *= other.z; w *= other.w;
        return *this;
    }

    Vector4& operator/=(const Vector4& other)
    {
        x /= other.x; y /= other.y; z /= other.z; w /= other.w;
        return *this;
    }

    Vector4& operator*=(float scalar)
    {
        x *= scalar; y *= scalar; z *= scalar; w *= scalar;
        return *this;
    }

    Vector4& operator/=(float scalar)
    {
        x /= scalar; y /= scalar; z /= scalar; w /= scalar;
        return *this;
    }

    bool operator==(const Vector4& other) const
    {
        return Mathf::Abs(x - other.x) < Mathf::epsilon &&
            Mathf::Abs(y - other.y) < Mathf::epsilon &&
            Mathf::Abs(z - other.z) < Mathf::epsilon &&
            Mathf::Abs(w - other.w) < Mathf::epsilon;
    }

    bool operator!=(const Vector4& other) const
    {
        return !(*this == other);
    }

    Vector4& operator=(const Vector4& other)
    {
        x = other.x; y = other.y; z = other.z; w = other.w;
        return *this;
    }

    float Magnitude() const
    {
        return Mathf::Sqrt(x * x + y * y + z * z + w * w);
    }

    float MagnitudeSquared() const
    {
        return x * x + y * y + z * z + w * w;
    }

    Vector4 Normalized() const
    {
        float mag = Magnitude();
        if (mag == 0)
            return Vector4(0, 0, 0, 0);
        return *this / mag;
    }

    float Dot(const Vector4& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    float Distance(const Vector4& other) const
    {
        return (*this - other).Magnitude();
    }

    float DistanceSquared(const Vector4& other) const
    {
        return (*this - other).MagnitudeSquared();
    }

    std::string ToString() const
    {
        return "(" + std::to_string(x) + ", " +
            std::to_string(y) + ", " +
            std::to_string(z) + ", " +
            std::to_string(w) + ")";
    }

    operator std::string() const
    {
        return ToString();
    }
};

const Vector4 Vector4::Zero = Vector4(0, 0, 0, 0);
const Vector4 Vector4::One = Vector4(1, 1, 1, 1);