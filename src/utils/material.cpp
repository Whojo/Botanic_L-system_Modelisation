#include "utils/material.hpp"

Material::Material(const std::string &name, const Vector3 &Kd)
    : name(name), Ka({0.2, 0.2, 0.2}), Kd(Kd), Ks({0.2,0.2,0.2}), Ns(323), d(1), illum(2)
{}
Material::Material(const std::string &name, const Vector3 &Ka, const Vector3 &Kd, const Vector3 &Ks,
         const double &Ns, const double &d, const size_t &illum)
    : name(name), Ka(Ka), Kd(Kd), Ks(Ks), Ns(Ns), d(d), illum(illum)
{}
void Material::write_mtl(const std::string &path) const
{
    const std::string filename = path + name + ".mtl"; 
    std::ofstream os(filename.c_str());
    if (os)
    {
        os << "newmtl" << " " << name << std::endl;
        os << std::setprecision(6) << "Ka" << " " <<
            Ka.x << " " << Ka.y << " " << Ka.z << std::endl;
        os << std::setprecision(6) << "Kd" << " " <<
            Kd.x << " " << Kd.y << " " << Kd.z << std::endl;
        os << std::setprecision(6) << "Ks" << " " <<
            Ks.x << " " << Ks.y << " " << Ks.z << std::endl;
        os << "Ns" << " " << Ns << std::endl;
        os << "d" << " " << d << std::endl;
        os << "illum" << " " << illum << std::endl;
    }
    else
        std::cerr << "Failed to open " << filename << std::endl;
}
