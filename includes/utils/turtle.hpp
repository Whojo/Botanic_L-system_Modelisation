#pragma once

#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "core/state.hpp"
#include "utils/drawer2D.hpp"
#include "utils/vector3.hpp"

using namespace cv;

using Palette = std::function<Scalar(char)>;
using LengthController = std::function<double(char)>;

void turtle2D(Drawer &drawer, std::string sentence, double angle,
            LengthController length_controller,
            Palette palette = [](const char) -> Scalar { return {0, 0, 0};},
            const int thickness = 2);

struct TurtleState
{
    Vector3 rotation;
    Vector3 position;
};

class Turtle3
{
public:
    Turtle3(const double &fixed_angle);
    Turtle3(const Vector3 &start, const double &fixed_angle);

    std::vector<double> RU(const double &angle);
    std::vector<double> RL(const double &angle);
    std::vector<double> RH(const double &angle);

    inline void push_state();
    inline bool pop_state();

    void create_obj_file(const std::string &filename,
                         const std::vector<Vector3> &pts,
                         const std::vector<std::vector<size_t>> &faces);
    std::vector<Vector3> compute(const core::State &sentence, const std::string &ignore,
            std::vector<std::vector<size_t>> &faces,
            const LengthController &length = [](const char) -> double {return 1;},
            const Palette &palette =  [](const char) -> Scalar {return {0, 0, 0};},
            const int &thickness = 2);

private:
    double fixed_angle; // used when no parameters given
    TurtleState state;
    std::deque<TurtleState> stack;
};

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