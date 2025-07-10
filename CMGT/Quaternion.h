#pragma once

#include "Vector3.h"
#include "Mathf.h"
#include "Matrix4x4.h"

#include <algorithm>
#include <cmath>

class Quaternion
{
public:
    float x, y, z, w;

    static const Quaternion identity;

    Quaternion(float x = 0, float y = 0, float z = 0, float w = 1) : x(x), y(y), z(z), w(w) {}

    static Quaternion FromAxisAngle(const Vector3& axis, float angleRadians)
    {
        Vector3 normAxis = axis.Normalized();
        float halfAngle = angleRadians * 0.5f;
        float sinHalf = Mathf::Sin(halfAngle);
        float cosHalf = Mathf::Cos(halfAngle);

        return Quaternion(
            normAxis.x * sinHalf,
            normAxis.y * sinHalf,
            normAxis.z * sinHalf,
            cosHalf
        );
    }

    static Quaternion FromEuler(float pitch, float yaw, float roll)
    {
        float cy = Mathf::Cos(yaw * 0.5f);
        float sy = Mathf::Sin(yaw * 0.5f);
        float cp = Mathf::Cos(pitch * 0.5f);
        float sp = Mathf::Sin(pitch * 0.5f);
        float cr = Mathf::Cos(roll * 0.5f);
        float sr = Mathf::Sin(roll * 0.5f);

        return Quaternion(
            sr * cp * cy - cr * sp * sy,
            cr * sp * cy + sr * cp * sy,
            cr * cp * sy - sr * sp * cy,
            cr * cp * cy + sr * sp * sy
        );
    }

    static Quaternion LookRotation(const Vector3& forward, const Vector3& up)
    {
        Vector3 f = forward.Normalized();
        Vector3 u = up.Normalized();
        Vector3 r = u.Cross(f).Normalized();
        u = f.Cross(r);

        float m00 = r.x, m01 = u.x, m02 = f.x;
        float m10 = r.y, m11 = u.y, m12 = f.y;
        float m20 = r.z, m21 = u.z, m22 = f.z;

        float trace = m00 + m11 + m22;
        Quaternion q;

        if (trace > 0.0f)
        {
            float s = Mathf::Sqrt(trace + 1.0f) * 2.0f;
            q.w = 0.25f * s;
            q.x = (m21 - m12) / s;
            q.y = (m02 - m20) / s;
            q.z = (m10 - m01) / s;
        }
        else if ((m00 > m11) && (m00 > m22))
        {
            float s = Mathf::Sqrt(1.0f + m00 - m11 - m22) * 2.0f;
            q.w = (m21 - m12) / s;
            q.x = 0.25f * s;
            q.y = (m01 + m10) / s;
            q.z = (m02 + m20) / s;
        }
        else if (m11 > m22)
        {
            float s = Mathf::Sqrt(1.0f + m11 - m00 - m22) * 2.0f;
            q.w = (m02 - m20) / s;
            q.x = (m01 + m10) / s;
            q.y = 0.25f * s;
            q.z = (m12 + m21) / s;
        }
        else
        {
            float s = Mathf::Sqrt(1.0f + m22 - m00 - m11) * 2.0f;
            q.w = (m10 - m01) / s;
            q.x = (m02 + m20) / s;
            q.y = (m12 + m21) / s;
            q.z = 0.25f * s;
        }

        return q.Normalized();
    }

    Vector3 ToEulerAngles() const
    {
        Vector3 angles;

        float sinp = 2.0f * (w * x + y * z);
        float cosp = 1.0f - 2.0f * (x * x + y * y);
        angles.x = std::atan2(sinp, cosp);

        float siny = 2.0f * (w * y - z * x);
        if (std::abs(siny) >= 1.0f)
            angles.y = siny > 0 ? Mathf::PI * 0.5f : -Mathf::PI * 0.5f;
        else
            angles.y = std::asin(siny);

        float sinr = 2.0f * (w * z + x * y);
        float cosr = 1.0f - 2.0f * (y * y + z * z);
        angles.z = std::atan2(sinr, cosr);

        return angles;
    }

    float Magnitude() const { return Mathf::Sqrt(x * x + y * y + z * z + w * w); }

    bool IsNormalized() const
    {
        return Mathf::Abs(Magnitude() - 1.0f) < Mathf::epsilon;
    }

    Quaternion Normalized() const
    {
        float mag = Magnitude();
        if (mag < Mathf::epsilon)
            return Quaternion(0, 0, 0, 1);
        return *this / mag;
    }

    Quaternion operator*(const Quaternion& other) const
    {
        return Quaternion(
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w,
            w * other.w - x * other.x - y * other.y - z * other.z
        );
    }

    Quaternion operator+(const Quaternion& other) const { return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w); }
    Quaternion operator-(const Quaternion& other) const { return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w); }
    Quaternion operator*(float scalar) const { return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar); }
    Quaternion operator/(float scalar) const { return Quaternion(x / scalar, y / scalar, z / scalar, w / scalar); }

    friend Quaternion operator*(float scalar, const Quaternion& q) { return q * scalar; }

    Quaternion& operator+=(const Quaternion& other)
    {
        x += other.x; y += other.y; z += other.z; w += other.w;
        return *this;
    }

    Quaternion& operator-=(const Quaternion& other)
    {
        x -= other.x; y -= other.y; z -= other.z; w -= other.w;
        return *this;
    }

    Quaternion& operator*=(const Quaternion& other)
    {
        *this = *this * other;
        return *this;
    }

    Quaternion operator-() const { return Quaternion(-x, -y, -z, -w); }

    bool operator==(const Quaternion& other) const
    {
        return Mathf::Abs(x - other.x) < Mathf::epsilon &&
            Mathf::Abs(y - other.y) < Mathf::epsilon &&
            Mathf::Abs(z - other.z) < Mathf::epsilon &&
            Mathf::Abs(w - other.w) < Mathf::epsilon;
    }

    bool operator!=(const Quaternion& other) const
    {
        return !(*this == other);
    }

    float Dot(const Quaternion& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    static float Angle(const Quaternion& a, const Quaternion& b)
    {
        float dot = std::min(std::abs(a.Dot(b)), 1.0f);
        return std::acos(dot) * 2.0f;
    }

    static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t)
    {
        return (a * (1 - t) + b * t).Normalized();
    }

    static Quaternion RotateTowards(const Quaternion& from, const Quaternion& to, float maxRadiansDelta)
    {
        float angle = Angle(from, to);
        if (angle == 0.0f)
            return to;
        float t = std::min(1.0f, maxRadiansDelta / angle);
        return Slerp(from, to, t);
    }

    static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t)
    {
        float dot = a.Dot(b);
        Quaternion end = b;

        if (dot < 0.0f)
        {
            dot = -dot;
            end = b * -1.0f;
        }

        if (dot > 0.9995f)
            return (a * (1 - t) + end * t).Normalized();

        float theta = std::acos(dot);
        float sinTheta = std::sin(theta);

        float aWeight = std::sin((1 - t) * theta) / sinTheta;
        float bWeight = std::sin(t * theta) / sinTheta;

        return (a * aWeight + end * bWeight).Normalized();
    }

    Quaternion Conjugate() const { return Quaternion(-x, -y, -z, w); }

    Quaternion Inverse() const
    {
        float magSq = x * x + y * y + z * z + w * w;
        if (magSq < Mathf::epsilon) return Quaternion(0, 0, 0, 1);
        return Conjugate() / magSq;
    }

    Vector3 Rotate(const Vector3& v) const
    {
        Quaternion qv(v.x, v.y, v.z, 0);
        Quaternion result = (*this) * qv * Inverse();
        return Vector3(result.x, result.y, result.z);
    }

    Quaternion Log() const
    {
        float vMag = std::sqrt(x * x + y * y + z * z);
        float angle = std::atan2(vMag, w);
        float coeff = (vMag < Mathf::epsilon) ? 0.0f : angle / vMag;
        return Quaternion(x * coeff, y * coeff, z * coeff, 0.0f);
    }

    Quaternion Exp() const
    {
        float angle = std::sqrt(x * x + y * y + z * z);
        float sinA = std::sin(angle);
        float cosA = std::cos(angle);
        float coeff = (angle < Mathf::epsilon) ? 1.0f : sinA / angle;
        return Quaternion(x * coeff, y * coeff, z * coeff, cosA);
    }

    Matrix4x4 ToRotationMatrix() const
    {
        Quaternion q = this->Normalized();
        float xx = q.x * q.x;
        float yy = q.y * q.y;
        float zz = q.z * q.z;
        float xy = q.x * q.y;
        float xz = q.x * q.z;
        float yz = q.y * q.z;
        float wx = q.w * q.x;
        float wy = q.w * q.y;
        float wz = q.w * q.z;

        return Matrix4x4(
            1 - 2 * (yy + zz), 2 * (xy - wz),     2 * (xz + wy),     0,
            2 * (xy + wz),     1 - 2 * (xx + zz), 2 * (yz - wx),     0,
            2 * (xz - wy),     2 * (yz + wx),     1 - 2 * (xx + yy), 0,
            0,                 0,                 0,                 1
        );
    }


    std::string ToString() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", "
            + std::to_string(z) + ", " + std::to_string(w) + ")";
    }

    operator std::string() const { return ToString(); }
};

const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);
