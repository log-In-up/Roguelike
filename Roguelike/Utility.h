#pragma once
#include "Vector.h"

namespace Roguelike
{
template <typename T>
bool InRect(GameEngine::Vector2D<T> rectTopLeft, GameEngine::Vector2D<T> rectSize, GameEngine::Vector2D<T> position)
{
    GameEngine::Vector2D<T> bottomRight = rectTopLeft + rectSize;
    return (rectTopLeft.x <= position.x && position.x < bottomRight.x) &&
           (rectTopLeft.y <= position.y && position.y < bottomRight.y);
}

template <typename T> bool InRange(T value, T minValue, T maxValue)
{
    return minValue <= value && value <= maxValue;
}

template <typename T> T Half(const T &value)
{
    constexpr float half = 0.5F;
    return half * value;
}
} // namespace Roguelike
