#pragma once

#include "Vector2.h"

#include <cstring>

class Matrix2x2
{
public:
    float m[2][2];

    Matrix2x2() { SetIdentity(); }

    Matrix2x2(float val)
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                m[i][j] = (i == j) ? val : 0.0f;
    }

    Matrix2x2(const float mat[2][2])
    {
        std::memcpy(m, mat, sizeof(m));
    }

    static Matrix2x2 Identity()
    {
        return Matrix2x2(1.0f);
    }

    void SetIdentity()
    {
        *this = Identity();
    }

    Matrix2x2 operator*(const Matrix2x2& other) const
    {
        Matrix2x2 result;
        for (int row = 0; row < 2; ++row)
            for (int col = 0; col < 2; ++col)
                result.m[row][col] =
                m[row][0] * other.m[0][col] +
                m[row][1] * other.m[1][col];
        return result;
    }

    Vector2 MultiplyVector(const Vector2& v) const
    {
        float x = m[0][0] * v.x + m[0][1] * v.y;
        float y = m[1][0] * v.x + m[1][1] * v.y;
        return Vector2(x, y);
    }

    Matrix2x2 Transposed() const
    {
        Matrix2x2 result;
        result.m[0][0] = m[0][0];
        result.m[0][1] = m[1][0];
        result.m[1][0] = m[0][1];
        result.m[1][1] = m[1][1];
        return result;
    }
};