#pragma once
#include <algorithm>

#include "Vector.h"
namespace GameEngine
{
template <typename T> struct Rect
{
    Vector2D<T> topLeft;
    Vector2D<T> bottomRight;

    Rect() : topLeft(0, 0), bottomRight(0, 0) {};
    Rect(T x1, T y1, T x2, T y2)
        : topLeft(std::min(x1, x2), std::min(y1, y2)), bottomRight(std::max(x1, x2), std::max(y1, y2)) {};
    Rect(const Vector2D<T> &topLeft, const Vector2D<T> &bottomRight)
        : Rect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y) {};

    Vector2D<T> GetSize()
    {
        return bottomRight - topLeft;
    };
};
using FloatRect = Rect<float>;
using IntRect = Rect<int>;
} // namespace GameEngine
