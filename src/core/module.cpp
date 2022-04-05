#include "core/module.hpp"


namespace core
{
    Module::Module(const char letter, const std::vector<double> &params)
        : letter{letter}, params{params}
    {}

    Module::Module(const char letter)
        : letter{letter}, params{}
    {}
}
