#pragma once

#include <vector>

#include "rule.hpp"


namespace core
{

    class LSystem
    {
    public:
        LSystem(std::string axiom_, std::vector<Rule> productions_);
        LSystem(std::string axiom_, std::vector<Rule> context_free_productions_,
                std::vector<Rule> context_sensitive_productions_);
        LSystem(std::string axiom_, std::vector<Rule> context_free_productions_,
                std::vector<Rule> context_sensitive_productions_, std::string ignore);

        std::string generate(const int n) const;

    private:
        std::string axiom_;
        std::vector<Rule> context_free_productions_;
        std::vector<Rule> context_sensitive_productions_;
        std::string ignore_; // Character ignored in context matching
    };
}
