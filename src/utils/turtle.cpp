#include "utils/turtle.hpp"

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
}

std::vector<Vector3> Turtle3::compute(const core::State &sentence, const std::string &ignore,
            std::vector<std::vector<size_t>> &faces,
            const LengthController &length,
            const Palette &palette,
            const int &thickness)
{
    std::vector<Vector3> points{ state.position };
    std::deque<size_t> face_index_stack;
    size_t former_index = 1;
    size_t index = 2;
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
                default:
                {
                    if (ignore.find(mod.letter) != std::string::npos)
                        break;
                    double len = (mod.params.size()) ? mod.params[0] : length(mod.letter);
                    state.position = state.position + (state.rotation[0] * len);
                    points.emplace_back(state.position);
                    faces.emplace_back(std::vector<size_t>{former_index, index});
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
                              const std::vector<std::vector<size_t>> &faces)
{
    std::ofstream os(filename.c_str());
    if (os)
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
    else
        std::cerr << "Failed to open " << filename << std::endl;
}
