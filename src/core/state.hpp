#pragma once

#include <string>
#include <vector>

#include "module.hpp"


namespace core
{
    class State
    {
    public:
        State(const std::vector<Module> &modules);
        State(const std::string &letters);
        State();

        std::vector<Module> get_modules() const;
        std::string get_letters() const;

        State& operator+=(const State &rhs);

    private:
        std::vector<Module> modules;
    };


}
