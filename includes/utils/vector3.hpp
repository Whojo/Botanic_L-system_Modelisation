#pragma once

#include <cmath>
#include <vector>

class Vector3
{
public:
    Vector3() = default;
    Vector3(double x, double y, double z)
        : x(x), y(y), z(z)
    {}

    inline Vector3 operator*(const double &c) const;
    inline Vector3 operator+(const Vector3 &v) const;
    inline Vector3 operator-(const Vector3 &v) const;
    inline Vector3 operator-() const;
    inline Vector3 normalize() const;
    inline bool operator==(const Vector3 &v) const;
    inline bool operator!=(const Vector3 &v) const;

    inline double dot(const Vector3 &v) const;
    inline Vector3 cross(const Vector3 &v) const;
    inline double norm() const;

public:
    double x;
    double y;
    double z;
};
Vector3 Vector3::operator*(const double &c) const
{
    return Vector3(x * c, y * c, z * c);
}
Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}
Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}
Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}
Vector3 Vector3::normalize() const
{
    double norme = norm();
    return Vector3(x / norme, y / norme, z / norme);
}
bool Vector3::operator==(const Vector3 &v) const
{
    return x == v.x && y == v.y && z == v.z;
}
bool Vector3::operator!=(const Vector3 &v) const
{
    return !(v == *this);
}
double Vector3::dot(const Vector3 &v) const
{
    return x * v.x + y * v.y + z * v.z;
}
Vector3 Vector3::cross(const Vector3 &v) const
{
    return Vector3((y * v.z) - (z * v.y),
                   (z * v.x) - (x * v.z),
                   (x * v.y) - (y * v.x));
}
double Vector3::norm() const
{
    return std::sqrt(x * x + y * y + z * z);
}
