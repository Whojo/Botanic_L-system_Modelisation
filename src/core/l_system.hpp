#pragma once

#include <vector>

#include "rule.hpp"


namespace core
{

    class LSystem
    {
    public:
        LSystem(std::string axiom_, std::vector<Rule> productions_);


        std::string generate(const int n) const;

    private:
        std::string axiom_;
        std::vector<Rule> productions_;
    };
}
