#include "state.hpp"


namespace core
{
    State::State(const std::vector<Module> &modules)
        : modules{modules}
    {}

    State::State(const std::string &letters)
        : modules{}
    {
        for (char letter : letters)
            modules.emplace_back(letter);
    }

    State::State()
        : modules{}
    {}

    std::vector<Module> State::get_modules() const
    {
        return modules;
    }
    
    std::string State::get_letters() const
    {
        std::string s;
        for (const Module &module: get_modules())
            s += module.letter;
        return s;
    }

    State& State::operator+=(const State &rhs)
    {
        const auto &rhs_mod = rhs.get_modules();
        this->modules.insert(this->modules.end(), rhs_mod.begin(), rhs_mod.end());
        return *this;
    }
}
