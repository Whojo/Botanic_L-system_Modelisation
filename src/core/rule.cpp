#include "rule.hpp"

#include <random>


namespace
{
    core::State select_randomly(const std::vector<core::State> &states)
    {
        return states[std::rand() % states.size()];

    }
} // namespace

namespace core
{
    Rule::Rule(const Module &pred, const State &successor)
        : application{[=](const Module &pred_, const State &, const State &) -> std::optional<State> {
            if (pred.letter != pred_.letter)
                return std::nullopt;
            return successor;
        }}
    {}

    Rule::Rule(const Module &pred, const std::vector<State> &successors)
        : application{[=](const Module &pred_, const State &, const State &) -> std::optional<State> {
            if (pred.letter != pred_.letter)
                return std::nullopt;
            return select_randomly(successors);
        }}
    {}

    Rule::Rule(const Module &pred, const State &successor,
               const ContextChecker &context_checker)
        : application{[=](const Module &pred_, const State &left,
                          const State &right) -> std::optional<State> {
            if (pred.letter != pred_.letter or not context_checker(left, right))
                return std::nullopt;
            return successor;
        }}
    {}

    Rule::Rule(const Module &pred, const std::vector<State> &successors,
               const ContextChecker &context_checker)
        : application{[=](const Module &pred_, const State &left,
                          const State &right) -> std::optional<State> {
            if (pred.letter != pred_.letter or not context_checker(left, right))
                return std::nullopt;
            return select_randomly(successors);
        }}
    {}

    Rule::Rule(const RuleApplication &application)
        : application{application}
    {}

    std::optional<State> Rule::apply(const Module &pred, const State &left, const State &right) const
    {
        return application(pred, left, right);
    }
} // namespace core
