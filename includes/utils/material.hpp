#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>

#include "vector3.hpp"

class Material
{
public:
    Material() = default;
    Material(const std::string &name, const Vector3 &Kd);
    Material(const std::string &name, const Vector3 &Ka, const Vector3 &Kd, const Vector3 &Ks,
             const double &Ns, const double &d, const size_t &illum);
    void write_mtl(const std::string &path) const;

public:
    const std::string name;

private:
    // For Ka, Kd, Ks, it is composed of RGB values, between 0-1
    Vector3 Ka; // Ambiant light color
    Vector3 Kd; // Diffuse color
    Vector3 Ks; // Specular color
    double Ns; // Specular exponential 0 - 1000
    double d; // Dissolved -> Inverse of transparency 0-1
    size_t illum; // Illumination model 1-10
};
