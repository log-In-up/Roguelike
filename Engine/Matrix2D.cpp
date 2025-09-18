#include "pch.h"

#include <array>
#include <cmath>
#include <iostream>
#include <numbers>
#include <vector>

#include "Matrix2D.h"
#include "Vector.h"

namespace GameEngine
{
constexpr float fullRotation = 360.0F;
constexpr float oneDegreeInRadians = std::numbers::pi_v<float> / (fullRotation * 0.5F);

Matrix2D::Matrix2D()
{
    m[0][0] = 1.0F;
    m[0][1] = 0.0F;
    m[0][2] = 0.0F;
    m[1][0] = 0.0F;
    m[1][1] = 1.0F;
    m[1][2] = 0.0F;
    m[2][0] = 0.0F;
    m[2][1] = 0.0F;
    m[2][2] = 1.0F;
}

Matrix2D::Matrix2D(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22)
{
    m[0][0] = a00;
    m[0][1] = a01;
    m[0][2] = a02;
    m[1][0] = a10;
    m[1][1] = a11;
    m[1][2] = a12;
    m[2][0] = a20;
    m[2][1] = a21;
    m[2][2] = a22;
}

Matrix2D::Matrix2D(Vector2Df position, float angle, Vector2Df scale)
{
    m[0][2] = position.x;
    m[1][2] = position.y;

    const float cosA = cos(angle * oneDegreeInRadians);
    const float sinA = sin(angle * oneDegreeInRadians);
    m[0][0] = cosA * scale.x;
    m[0][1] = sinA * scale.x;
    m[1][0] = -sinA * scale.y;
    m[1][1] = cosA * scale.y;

    m[2][0] = 0.0F;
    m[2][1] = 0.0F;
    m[2][2] = 1.0F;
}

Matrix2D Matrix2D::operator*(const Matrix2D &other) const
{
    Matrix2D result;
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            result.m[row][col] =
                m[row][0] * other.m[0][col] + m[row][1] * other.m[1][col] + m[row][2] * other.m[2][col];
        }
    }
    return result;
}

const std::array<std::array<float, 3>, 3> &Matrix2D::GetMatrix() const
{
    return m;
}

Matrix2D Matrix2D::GetInversed() const
{
    Matrix2D result;
    const float determinant = (m[0][0] * m[1][1] * m[2][2]) - (m[0][0] * m[1][2] * m[2][1]) -
                              (m[0][1] * m[1][0] * m[2][2]) + (m[0][1] * m[1][2] * m[2][0]) +
                              (m[0][2] * m[1][0] * m[2][1]) - (m[0][2] * m[1][1] * m[2][0]);

    const float inversedDeterminant = 1.0F / determinant;

    Matrix2D minor(0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F);

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            minor.m[row][column] = GetMinor(row, column);
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result.m[i][j] = inversedDeterminant * minor.m[j][i];
        }
    }

    return result;
}

void Matrix2D::Print() const
{
    for (int row = 0; row < 3; ++row)
    {
        std::cout << "| ";
        for (int col = 0; col < 3; ++col)
        {
            std::cout << m[row][col] << " ";
        }
        std::cout << "|\n";
    }
    std::cout << std::endl;
}

float Matrix2D::GetMinor(const int row, const int column) const
{
    std::vector<std::vector<float>> submatrix(2, std::vector<float>(2));
    int submatrixRow = 0;
    int submatrixCol = 0;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (i != row && j != column)
            {
                submatrix[submatrixRow][submatrixCol] = m[i][j];
                ++submatrixCol;
                if (submatrixCol == 2)
                {
                    submatrixCol = 0;
                    ++submatrixRow;
                }
            }
        }
    }

    float minor = (submatrix[0][0] * submatrix[1][1]) - (submatrix[1][0] * submatrix[0][1]);
    if ((row + column) % 2 == 1)
    {
        minor *= -1.0F;
    }
    return minor;
}
} // namespace GameEngine