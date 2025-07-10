#pragma once
#include <string>s
#include "Mathf.h"


class Vector3
{
public:
    float x, y, z;

    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 Up;
    static const Vector3 Down;
    static const Vector3 Left;
    static const Vector3 Right;
    static const Vector3 Forward;
    static const Vector3 Back;

    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) { }

    Vector3 operator+(const Vector3& other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(const Vector3& other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3 operator/(const Vector3& other) const
    {
        return Vector3(x / other.x, y / other.y, z / other.z);
    }

    Vector3 operator*(float scalar) const
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3 operator/(float scalar) const
    {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    Vector3& operator+=(const Vector3& other)
    {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& other)
    {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    Vector3& operator*=(const Vector3& other)
    {
        x *= other.x; y *= other.y; z *= other.z;
        return *this;
    }

    Vector3& operator/=(const Vector3& other)
    {
        x /= other.x; y /= other.y; z /= other.z;
        return *this;
    }

    Vector3& operator*=(float scalar)
    {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    Vector3& operator/=(float scalar)
    {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }

    bool operator==(const Vector3& other) const
    {
        return Mathf::Abs(x - other.x) < Mathf::epsilon &&
            Mathf::Abs(y - other.y) < Mathf::epsilon &&
            Mathf::Abs(z - other.z) < Mathf::epsilon;

    }

    bool operator!=(const Vector3& other) const
    {
        return Mathf::Abs(x - other.x) > Mathf::epsilon ||
            Mathf::Abs(y - other.y) > Mathf::epsilon ||
            Mathf::Abs(z - other.z) > Mathf::epsilon;

    }

    Vector3& operator=(const Vector3& other)
    {
        x = other.x; y = other.y; z = other.z;
        return *this;
    }

    float Magnitude() const 
    { 
        return Mathf::Sqrt(x * x + y * y + z * z);
    }

    float MagnitudeSquared() const
    {
        return x * x + y * y + z * z;
    }

    Vector3 Normalized() const
    {
        float mag = Magnitude();

        if (mag == 0) 
            return Vector3(0, 0, 0);

        return *this / mag;
    }

    float Dot(const Vector3& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Cross(const Vector3& other) const
    {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    float AngleBetween(const Vector3& other) const
    {
        float dot = Normalized().Dot(other.Normalized());
        dot = Mathf::Clamp(dot, -1, 1);

        return std::acos(dot);
    }

    float AngleBetweenDegrees(const Vector3& other) const
    {
        return AngleBetween(other) * (180.0f / Mathf::PI);
    }

    float SignedAngleBetween(const Vector3& other, const Vector3& axis) const
    {
        Vector3 a = this->Normalized();
        Vector3 b = other.Normalized();
        float angle = Mathf::Clamp(a.Dot(b), -1, 1);
        Vector3 cross = a.Cross(b);
        if (axis.Dot(cross) < 0)
            angle = -angle;
        return angle;
    }

    float SignedAngleBetweenDegrees(const Vector3& other, const Vector3& axis) const
    {
        return SignedAngleBetween(other, axis) * (180.0f / Mathf::PI);
    }

    Vector3 RotatedAround(const Vector3& axis, float angleRadians) const
    {
        Vector3 u = axis.Normalized();
        float cosA = std::cos(angleRadians);
        float sinA = std::sin(angleRadians);

        return (*this * cosA) +
            (u.Cross(*this) * sinA) +
            (u * (u.Dot(*this)) * (1.0f - cosA));
    }

    Vector3 RotatedAroundDegrees(const Vector3& axis, float angleDegrees) const
    {
        return RotatedAround(axis, angleDegrees * (Mathf::PI / 180.0f));
    }

    float Distance(const Vector3& other) const
    {
        return (*this - other).Magnitude();
    }

    float DistanceSquared(const Vector3& other) const
    {
        return (*this - other).MagnitudeSquared();
    }

    std::string ToString() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

    operator std::string() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }
};

const Vector3 Vector3::Zero = Vector3(0, 0, 0);
const Vector3 Vector3::One = Vector3(1, 1, 1);
const Vector3 Vector3::Up = Vector3(0, 1, 0);
const Vector3 Vector3::Down = Vector3(0, -1, 0);
const Vector3 Vector3::Left = Vector3(-1, 0, 0);
const Vector3 Vector3::Right = Vector3(1, 0, 0);
const Vector3 Vector3::Forward = Vector3(0, 0, 1);
const Vector3 Vector3::Back = Vector3(0, 0, -1);