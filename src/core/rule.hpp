#pragma once

#include <optional>
#include <functional>
#include <string>
#include <vector>
#include <memory>

#include "module.hpp"
#include "state.hpp"


using ostr = std::optional<std::string>;
using cstr = const std::string;

namespace core
{
    using RuleApplication = std::function<std::optional<State>(const Module&, const State&,
        const State&)>;
    using ContextChecker = std::function<bool(const State&, const State&)>;

    class Rule
    {
    public:
        Rule(const Module &pred, const State &successor);
        Rule(const Module &pred, const std::vector<State> &successors);
        Rule(const Module &pred, const State &successor,
             const ContextChecker &context_checker);
        Rule(const Module &pred, const std::vector<State> &successors,
             const ContextChecker context_checker);
        Rule(const RuleApplication &application);

        std::optional<State> apply(const Module &pred, const State &left, const State &right) const;

    private:
        const RuleApplication application;
    };
}
