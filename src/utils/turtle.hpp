#pragma once

#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>

#include "../core/state.hpp"
#include "drawer2D.hpp"

using namespace cv;

using Palette = std::function<Scalar(char)>;
using LengthController = std::function<double(char)>;

void turtle2D(Drawer &drawer, std::string sentence, double angle,
            LengthController length_controller,
            Palette palette = [](const char) -> Scalar { return {0, 0, 0};},
            const int thickness = 2);
