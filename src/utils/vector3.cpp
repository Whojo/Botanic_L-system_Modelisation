#include "vector3.hpp"

Vector3::Vector3(double x, double y, double z)
    : x(x), y(y), z(z)
{}

inline Vector3 Vector3::operator*(const double &c) const
{
    return Vector3(x * c, y * c, z * c);
}
inline Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}
inline Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}
inline Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}
inline Vector3 Vector3::normalize() const
{
    double norme = norm();
    return Vector3(x / norme, y / norme, z / norme);
}
inline bool Vector3::operator==(const Vector3 &v) const
{
    return x == v.x && y == v.y && z == v.z;
}
inline bool Vector3::operator!=(const Vector3 &v) const
{
    return !(v == *this);
}

inline double Vector3::dot(const Vector3 &v) const
{
    return x * v.x + y * v.y + z * v.z;
}
inline Vector3 Vector3::cross(const Vector3 &v) const
{
    return Vector3((y * v.z) - (z * v.y),
                   (z * v.x) - (x * v.z),
                   (x * v.y) - (y * v.x));
}
inline double Vector3::norm() const
{
    return std::sqrt(x * x + y * y + z * z);
}
