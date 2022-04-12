#include "utils/turtle.hpp"
#include <cmath>

void turtle2D(Drawer &drawer, std::string sentence, double angle,
            LengthController length_controller, Palette palette,
            const int thickness)
{
    for (size_t i = 0; i < sentence.length(); i++)
    {
        char c = sentence[i];
        switch(c)
        {
            case 'X':
                break;
            case '+':
                drawer.add_angle(angle);
                break;
            case '-':
                drawer.add_angle(-angle);
                break;
            case '[':
                drawer.push_state();
                break;
            case ']':
                if (!drawer.pop_state())
                    std::cerr << "Empty pop" << std::endl;
                break;
            default:
                drawer.draw_line(palette(c), thickness, length_controller(c));
        }
    }
}

std::vector<double> Turtle3::RU(const double &angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    return std::vector<double>{ c, s, 0,
                               -s, c, 0,
                                0, 0, 1, };
}
std::vector<double> Turtle3::RL(const double &angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    return std::vector<double>{ c, 0,-s,
                                0, 1, 0,
                                s, 0, c, };
}
std::vector<double> Turtle3::RH(const double &angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    return std::vector<double>{ 1, 0, 0,
                                0, c,-s,
                                0, s, c, };
}

Turtle3::Turtle3(const double &fixed_angle)
{
    this->fixed_angle = fixed_angle;
    state = TurtleState{
        std::vector<Vector3>{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        },
        Vector3{0,0,0}
    };
}

namespace
{
    void rotate(std::vector<Vector3> &rotation, const std::vector<double> &rot_mat)
    {
        auto x = rotation[0];
        auto y = rotation[1];
        auto z = rotation[2];

        rotation = std::vector{ x * rot_mat[0] + y * rot_mat[3] + z * rot_mat[6],
                                x * rot_mat[1] + y * rot_mat[4] + z * rot_mat[7],
                                x * rot_mat[2] + y * rot_mat[5] + z * rot_mat[8] };
    }
    double non_null_coordinate(const Vector3 &v)
    {
        double value = 0;
        double epsilon = 1e-6;
        if (v.x > epsilon)
            return v.x;
        if (v.y > epsilon)
            return v.y;
        return v.z;
    }

    void add_surface_to_faces(std::vector<std::vector<size_t>> &faces,
                              const size_t start, const size_t end)
    {
        if (start >= end)
        {
            std::cerr << "Empty or negative (??) surface" << std::endl;
            return;
        }

        auto cur = end;
        std::vector<size_t> face{cur};
        while (start < cur)
        {
            cur = faces.back()[0];
            face.emplace_back(cur);
            faces.pop_back(); // Removed edges of the surface
        }

        faces.emplace_back(face);
    }
}

std::vector<Vector3> Turtle3::compute(const core::State &sentence, const std::string &ignore,
            std::vector<std::vector<size_t>> &faces,
            std::vector<double> &thicknesses,
            //const std::vector<Material> &materials,
            double thickness,
            const LengthController &length)
{
    std::vector<Vector3> points{ state.position };
    std::deque<size_t> face_index_stack;
    size_t former_index = 1;
    size_t index = 2;
    std::optional<size_t> starting_face_id = std::nullopt;
    for (size_t i = 0; i < sentence.get_modules().size(); i++)
    {
            core::Module mod = sentence.get_modules()[i];
            switch (mod.letter)
            {
                case 'X':
                    break;
                case '+':
                {
                    std::vector<double> ru = RU(mod.params.size() == 1 ? mod.params[0] : fixed_angle);
                    rotate(state.rotation, ru);
                    break;
                }
                case '-':
                {
                    std::vector<double> ru = RU(-fixed_angle);
                    rotate(state.rotation, ru);
                    break;
                }
                case '&':
                {
                    std::vector<double> rl = RL(mod.params.size() == 1 ? mod.params[0] : fixed_angle);
                    rotate(state.rotation, rl);
                    break;
                }
                case '^':
                {
                    std::vector<double> rl = RL(-fixed_angle);
                    rotate(state.rotation, rl);
                    break;
                }
                case '\\':
                {
                    std::vector<double> rh = RH(fixed_angle);
                    rotate(state.rotation, rh);
                    break;
                }
                case '/':
                {
                    std::vector<double> rh = RH(mod.params.size() == 1 ? mod.params[0] : -fixed_angle);
                    rotate(state.rotation, rh);
                    break;
                }
                case '|':
                {
                    std::vector<double> ru = RU(pi); // 180°
                    rotate(state.rotation, ru);
                    break;
                }
                case '[':
                {
                    face_index_stack.push_front(former_index);
                    push_state();
                    break;
                }
                case ']':
                {
                    former_index = face_index_stack.front();
                    face_index_stack.pop_front();
                    if (!pop_state())
                        std::cerr << "Empty pop" << std::endl;
                    break;
                }
                case '{':
                {
                    starting_face_id = former_index;
                    break;
                }
                case '}':
                {
                    if (starting_face_id.has_value())
                        add_surface_to_faces(faces, starting_face_id.value(), former_index);

                    starting_face_id = std::nullopt;
                    break;
                }
                case '!':
                    thickness *= 0.80;
                    break;
                default:
                {
                    if (ignore.find(mod.letter) != std::string::npos)
                        break;
                    double len = (mod.params.size()) ? mod.params[0] : length(mod.letter);
                    double t = (mod.params.size() >= 2) ? mod.params[1] : thickness;
                    state.position = state.position + (state.rotation[0] * len);
                    points.emplace_back(state.position);
                    faces.emplace_back(std::vector<size_t>{former_index, index});
                    thicknesses.emplace_back(t);
                    former_index = index;
                    index += 1;
                    break;
                }
            }
    }
    return points;
}

void Turtle3::create_obj_file(const std::string &filename,
                              const std::vector<Vector3> &pts,
                              const std::vector<std::vector<size_t>> &faces,
                              const std::optional<std::vector<Material>> &o_materials)
{
    std::ofstream os(filename.c_str());
    if (os)
    {
        if (o_materials.has_value())
        {
            std::vector<Material> materials = o_materials.value();
            size_t mat_size = materials.size();
            std::cout << "has value | mat.size = " << mat_size << std::endl;
            if (mat_size > 0)
            {
                os << "mtllib";
                for (const auto &mat : materials)
                    os << " " << mat.name << ".mtl";
                os << std::endl;
            }
            for (const Vector3 &pt : pts)
                os << "v " << std::setprecision(7) << pt.x << " " << pt.y << " " << pt.z << std::endl; 
            std::vector<std::vector<size_t>> leaf_faces;
            std::vector<std::vector<size_t>> trunc_faces;
            for (const std::vector<size_t> face : faces)
            {
                if (face.size() > 4)
                    leaf_faces.emplace_back(face);
                else
                    trunc_faces.emplace_back(face);
            }
            if (mat_size > 0)
            {
                os << "usemtl " << materials[mat_size - 1].name << std::endl;
                std::cout << "trunc_faces -> " << trunc_faces.size() << std::endl;
                for (const std::vector<size_t> face : trunc_faces)
                {
                    os << "f";
                    for (const size_t vector_index : face)
                        os << " " << vector_index;
                    os << std::endl;
                }
            }
            os << "usemtl " << materials[0].name << std::endl;
            std::cout << "leaf_faces -> " << leaf_faces.size() << std::endl;
            for (const std::vector<size_t> face : leaf_faces)
            {
                os << "f";
                for (const size_t vector_index : face)
                    os << " " << vector_index;
                os << std::endl;
            }
        }
        else
        {
            for (const Vector3 &pt : pts)
                os << "v " << std::setprecision(7) << pt.x << " " << pt.y << " " << pt.z << std::endl; 
            for (const std::vector<size_t> face : faces)
            {
                os << "f";
                for (const size_t vector_index : face)
                    os << " " << vector_index;
                os << std::endl;
            }
        }
    }
    else
        std::cerr << "Failed to open " << filename << std::endl;
}

void Turtle3::to_cylinder(const double &radius, const size_t &discretisation,
                          std::vector<Vector3> &pts,
                          std::vector<std::vector<size_t>> &faces,
                          std::vector<double> &thicknesses)
{
    std::vector<Vector3> new_pts;
    std::vector<std::vector<size_t>> new_faces;
    size_t new_y = 1;
    size_t index = 0;
    for (const auto &face : faces)
    {
        // On a complexer form: e.g. a leaf
        if (face.size() != 2)
        {
            std::vector<size_t> new_face;
            for (const auto &pt : face)
            {
                new_pts.emplace_back(pts[pt - 1]);
                new_face.emplace_back(new_y++);
            }
            new_faces.emplace_back(new_face);
            continue;
        }

        double edge_thickness = thicknesses[index++];
        size_t i1 = face[0];
        size_t i2 = face[1];
        Vector3 v1 = pts[i1 - 1];
        Vector3 v2 = pts[i2 - 1];
        Vector3 dir = (v2 - v1).normalize();
        Vector3 pdir = dir.cross({dir.x + pi, dir.y + pi, dir.z + pi}).normalize();
        std::vector<Vector3> rot= {
            dir,
            pdir,
            dir.cross(pdir).normalize(),
        };
        double angle = pi / discretisation;
        Vector3 former1 = v1 + (rot[2] * radius * edge_thickness);
        Vector3 former2 = v2 + (rot[2] * radius * edge_thickness);
        new_pts.emplace_back(former1);
        new_pts.emplace_back(former2);
        size_t y = new_y;
        for (size_t i = 1; i < discretisation * 2; i++, y+=2)
        {
            rotate(rot, RH(angle));
            Vector3 new1 = v1 + (rot[2] * radius * edge_thickness);
            Vector3 new2 = v2 + (rot[2] * radius * edge_thickness);
            new_pts.emplace_back(new1);
            new_pts.emplace_back(new2);
            new_faces.emplace_back(std::vector<size_t>{y, y+1, y+3, y+2});
            former1 = new1;
            former2 = new2;
        }
        size_t max_index = discretisation * 4;
        new_faces.emplace_back(std::vector<size_t>{y, y+1, new_y + 1, new_y});
        new_y += max_index;
    }
    pts = new_pts;
    faces = new_faces;
}
