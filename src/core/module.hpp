#pragma once

#include <vector>


namespace core
{
    class Module
    {
    public:
        Module(const char letter, const std::vector<double> &params);
        Module(const char letter);

    public:
        char letter;
        std::vector<double> params;
    };
}
