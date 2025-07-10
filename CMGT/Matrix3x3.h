#pragma once

#include <cstring>
#include <cmath>

#include "Vector3.h"
#include "Quaternion.h"
#include "Mathf.h"

class Matrix3x3
{
public:
    float m[3][3];

    Matrix3x3() { SetIdentity(); }

    Matrix3x3(float val)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] = (i == j) ? val : 0.0f;
    }

    Matrix3x3(const float mat[3][3])
    {
        std::memcpy(m, mat, sizeof(m));
    }

    static Matrix3x3 Identity()
    {
        return Matrix3x3(1.0f);
    }

    void SetIdentity()
    {
        *this = Identity();
    }

    Matrix3x3 operator*(const Matrix3x3& other) const
    {
        Matrix3x3 result;
        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                result.m[row][col] =
                    m[row][0] * other.m[0][col] +
                    m[row][1] * other.m[1][col] +
                    m[row][2] * other.m[2][col];
            }
        }
        return result;
    }

    Vector3 operator*(const Vector3& v) const
    {
        return Vector3(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
        );
    }

    Matrix3x3 Transposed() const
    {
        Matrix3x3 result;
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                result.m[row][col] = m[col][row];
        return result;
    }

    float Determinant() const
    {
        return
            m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
            m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
            m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    Matrix3x3 Inverse() const
    {
        float det = Determinant();
        if (Mathf::Abs(det) < Mathf::epsilon)
            return Matrix3x3();

        float invDet = 1.0f / det;

        Matrix3x3 result;

        result.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
        result.m[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) * invDet;
        result.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;

        result.m[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) * invDet;
        result.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
        result.m[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) * invDet;

        result.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet;
        result.m[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) * invDet;
        result.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet;

        return result;
    }

    static Matrix3x3 Rotate(const Quaternion& q)
    {
        Matrix3x3 result;
        float x = q.x * 2.0f, y = q.y * 2.0f, z = q.z * 2.0f;
        float xx = q.x * x, yy = q.y * y, zz = q.z * z;
        float xy = q.x * y, xz = q.x * z, yz = q.y * z;
        float wx = q.w * x, wy = q.w * y, wz = q.w * z;

        result.m[0][0] = 1.0f - (yy + zz);
        result.m[0][1] = xy - wz;
        result.m[0][2] = xz + wy;

        result.m[1][0] = xy + wz;
        result.m[1][1] = 1.0f - (xx + zz);
        result.m[1][2] = yz - wx;

        result.m[2][0] = xz - wy;
        result.m[2][1] = yz + wx;
        result.m[2][2] = 1.0f - (xx + yy);

        return result;
    }
};
