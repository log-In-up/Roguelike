#pragma once
#include <cmath>
#include <concepts>
#include <numbers>

namespace GameEngine
{
template <typename T> struct Vector2D
{
    T x;
    T y;

    Vector2D() : x(T(0)), y(T(0)) {};
    Vector2D(T x, T y) : x(x), y(y) {};

    Vector2D &operator-()
    {
        x *= -1;
        y *= -1;
        return *this;
    }

    Vector2D &operator+=(const Vector2D &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D &operator-=(const Vector2D &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2D &operator*=(const T &scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D &operator*=(const Vector2D &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    T DotProduct(const Vector2D &other) const
    {
        return x * other.x + y * other.y;
    }

    float GetLength() const
    {
        return sqrtf(x * x + y * y);
    }
};

using Vector2Df = Vector2D<float>;
using Vector2Di = Vector2D<int>;
using Position = Vector2Df;

template <typename T> Vector2D<T> operator+(Vector2D<T> left, const Vector2D<T> &right)
{
    return left += right;
}

template <typename T> Vector2D<T> operator-(Vector2D<T> left, const Vector2D<T> &right)
{
    return left -= right;
}

template <typename T> bool operator==(const Vector2D<T> &left, const Vector2D<T> &right)
{
    return (left.x == right.x) && (left.y == right.y);
}

template <typename T> bool operator!=(const Vector2D<T> &left, const Vector2D<T> &right)
{
    return !(left == right);
}

template <typename T> T DotProduct(Vector2D<T> left, const Vector2D<T> &right)
{
    return left.DotProduct(right);
}

template <typename T> Vector2D<T> operator*(Vector2D<T> left, const Vector2D<T> &rigth)
{
    return left *= rigth;
}

template <typename T> Vector2D<T> operator*(Vector2D<T> left, const T scalar)
{
    return left *= scalar;
}

template <typename T> Vector2D<T> operator*(const T scalar, Vector2D<T> rigth)
{
    return rigth *= scalar;
}

template <typename U, typename V> U Convert(const V &v)
{
    return {static_cast<decltype(U::x)>(v.x), static_cast<decltype(U::y)>(v.y)};
}

template <typename T>
    requires std::floating_point<T>
T DegreeToRadian(const T angle)
{
    return angle * std::numbers::pi_v<T> / 180.0F;
}

template <typename T>
    requires std::floating_point<T>
T RadianToDegree(const T angle)
{
    return angle * std::numbers::inv_pi_v<T> * 180.0F;
}

template <typename T> float AngleDegree(const Vector2D<T> &firstVector, const Vector2D<T> &secondVector)
{
    return RadianToDegree(Angle(firstVector, secondVector));
}

template <typename T> float Angle(const Vector2D<T> &firstVector, const Vector2D<T> &secondVector)
{
    float angleCos = static_cast<float>(DotProduct(firstVector, secondVector)) /
                     (firstVector.GetLength() * secondVector.GetLength());
    return acosf(angleCos);
}

template <typename T>
    requires std::floating_point<T>
Vector2D<T> Normalized(const Vector2D<T> &vector)
{
    float length = vector.GetLength();
    if (length > 0.0F)
    {
        return vector * (1.0F / vector.GetLength());
    }
    return {0.0F, 0.0F};
}

template <typename T>
    requires std::floating_point<T>
void Rotate(Vector2D<T> &vector, float angle)
{
    auto radianAngle = DegreeToRadian(angle);
    T newX = cosf(radianAngle) * vector.x - sinf(radianAngle) * vector.y;
    T newY = sinf(radianAngle) * vector.x + cosf(radianAngle) * vector.y;
    vector.x = newX;
    vector.y = newY;
}
} // namespace GameEngine