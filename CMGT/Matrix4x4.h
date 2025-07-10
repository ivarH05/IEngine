#pragma once

#include <cstring>

#include "Mathf.h"
#include "Vector3.h"
#include "Quaternion.h"

class Matrix4x4
{
public:
    float m[4][4];

    Matrix4x4() { SetIdentity(); }

    Matrix4x4(float val)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? val : 0.0f;
    }

    Matrix4x4(const float mat[4][4])
    {
        std::memcpy(m, mat, sizeof(m));
    }

    static Matrix4x4 Identity()
    {
        return Matrix4x4(1.0f);
    }

    void SetIdentity()
    {
        *this = Identity();
    }

    Matrix4x4 operator*(const Matrix4x4& other) const
    {
        Matrix4x4 result;
        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col)
                result.m[row][col] =
                m[row][0] * other.m[0][col] +
                m[row][1] * other.m[1][col] +
                m[row][2] * other.m[2][col] +
                m[row][3] * other.m[3][col];
        return result;
    }

    Vector3 MultiplyPoint(const Vector3& v) const
    {
        float x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
        float y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
        float z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
        float w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];
        if (w != 0.0f)
        {
            x /= w; y /= w; z /= w;
        }
        return Vector3(x, y, z);
    }

    Vector3 MultiplyDirection(const Vector3& v) const
    {
        float x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
        float y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
        float z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
        return Vector3(x, y, z);
    }

    Matrix4x4 Transposed() const
    {
        Matrix4x4 result;
        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col)
                result.m[row][col] = m[col][row];
        return result;
    }

    static Matrix4x4 Translate(const Vector3& v)
    {
        Matrix4x4 result = Identity();
        result.m[0][3] = v.x;
        result.m[1][3] = v.y;
        result.m[2][3] = v.z;
        return result;
    }

    static Matrix4x4 Scale(const Vector3& v)
    {
        Matrix4x4 result;
        result.m[0][0] = v.x;
        result.m[1][1] = v.y;
        result.m[2][2] = v.z;
        result.m[3][3] = 1.0f;
        return result;
    }

    static Matrix4x4 Rotate(const Quaternion& q)
    {
        Matrix4x4 result;
        float x = q.x * 2.0f, y = q.y * 2.0f, z = q.z * 2.0f;
        float xx = q.x * x, yy = q.y * y, zz = q.z * z;
        float xy = q.x * y, xz = q.x * z, yz = q.y * z;
        float wx = q.w * x, wy = q.w * y, wz = q.w * z;

        result.m[0][0] = 1.0f - (yy + zz);
        result.m[0][1] = xy - wz;
        result.m[0][2] = xz + wy;
        result.m[0][3] = 0.0f;

        result.m[1][0] = xy + wz;
        result.m[1][1] = 1.0f - (xx + zz);
        result.m[1][2] = yz - wx;
        result.m[1][3] = 0.0f;

        result.m[2][0] = xz - wy;
        result.m[2][1] = yz + wx;
        result.m[2][2] = 1.0f - (xx + yy);
        result.m[2][3] = 0.0f;

        result.m[3][0] = 0.0f;
        result.m[3][1] = 0.0f;
        result.m[3][2] = 0.0f;
        result.m[3][3] = 1.0f;

        return result;
    }

    static Matrix4x4 TRS(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
    {
        return Translate(position) * Rotate(rotation) * Scale(scale);
    }
};
