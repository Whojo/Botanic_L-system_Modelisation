#pragma once

#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>

#include "../core/state.hpp"
#include "drawer2D.hpp"
#include "vector3.hpp"

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
    Turtle3(const double &angle);

    std::vector<double> RU(const double &angle);
    std::vector<double> RL(const double &angle);
    std::vector<double> RH(const double &angle);

    inline void push_state();
    inline bool pop_state();

    std::vector<Vector3> compute(const Vector3 &start,const core::State &sentence, 
            const LengthController &length = [](const char) -> double {return 10;},
            const Palette &palette =  [](const char) -> Scalar {return {0, 0, 0};},
            const int &thickness = 2);
private:
    double fixed_angle; // used when no parameters given
    TurtleState state;
    std::deque<TurtleState> stack;
};
