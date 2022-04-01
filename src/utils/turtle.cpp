#include "turtle.hpp"


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

inline Vector3 rotate(const std::vector<double> &rot_mat, const Vector3 &v)
{
    return Vector3(v.x * rot_mat[0] + v.y * rot_mat[3] + v.z * rot_mat[6],
                   v.x * rot_mat[1] + v.y * rot_mat[4] + v.z * rot_mat[7],
                   v.x * rot_mat[2] + v.y * rot_mat[5] + v.z * rot_mat[8]);
}

inline void Turtle3::push_state()
{
    stack.push_front(TurtleState{state.rotation, state.position});
}
inline bool Turtle3::pop_state()
{
    if (!stack.empty())
    {
        // pop_front return void :c
        state = stack.front();
        stack.pop_front();
        return true;
    }
    return false;
}

std::vector<Vector3> Turtle3::compute(const Vector3 &start,const core::State &sentence,
            const LengthController &length,
            const Palette &palette,
            const int &thickness)
{
    std::vector<Vector3> points{ start };
    Vector3 current_point = start;
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
                    state.rotation = rotate(ru, state.rotation);
                    break;
                }
                case '-':
                {
                    std::vector<double> ru = RU(-fixed_angle);
                    state.rotation = rotate(ru, state.rotation);
                    break;
                }
                case '&':
                {
                    std::vector<double> rl = RL(mod.params.size() == 1 ? mod.params[0] : fixed_angle);
                    state.rotation = rotate(rl, state.rotation);
                    break;
                }
                case '^':
                {
                    std::vector<double> rl = RL(-fixed_angle);
                    state.rotation = rotate(rl, state.rotation);
                    break;
                }
                case '\\':
                {
                    std::vector<double> rh = RH(fixed_angle);
                    state.rotation = rotate(rh, state.rotation);
                    break;
                }
                case '/':
                {
                    std::vector<double> rh = RH(mod.params.size() == 1 ? mod.params[0] : -fixed_angle);
                    state.rotation = rotate(rh, state.rotation);
                    break;
                }
                case '|':
                {
                    std::vector<double> ru = RU(pi); // 180°
                    state.rotation = rotate(ru, state.rotation);
                    break;
                }
                case '[':
                    push_state();
                    break;
                case ']':
                    if (!pop_state())
                        std::cerr << "Empty pop" << std::endl;
                    break;
                default:
                {
                    double len = (mod.params.size()) ? mod.params[0] : length(mod.letter) ;
                    current_point = current_point + (state.rotation * len);
                    points.emplace_back(TurtleState{state.rotation, current_point});
                    break;
                }
            }
            state = TurtleState{state.rotation, current_point};
    }
    return points;
}
