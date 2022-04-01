#include <cmath>


class Vector3
{
public:
    Vector3();
    Vector3(double x, double y, double z);

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
