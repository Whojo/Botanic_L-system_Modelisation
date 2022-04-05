#pragma once

#include <vector>

#include "core/rule.hpp"


namespace core
{

    class LSystem
    {
    public:
        LSystem(const State &axiom_, const std::vector<Rule> &productions_);
        LSystem(const State &axiom_, const std::vector<Rule> &context_free_productions_,
                const std::vector<Rule> &context_sensitive_productions_);
        LSystem(const State &axiom_, const std::vector<Rule> &context_free_productions_,
                const std::vector<Rule> &context_sensitive_productions_, const std::string &ignore);

        State generate(const int n) const;

    private:
        const State axiom_;
        std::vector<Rule> context_free_productions_;
        std::vector<Rule> context_sensitive_productions_;
        const std::string ignore_; // Character ignored in context matching
    };
}
