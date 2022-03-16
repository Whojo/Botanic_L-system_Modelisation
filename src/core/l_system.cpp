#include "l_system.hpp"
#include <iostream>

namespace core
{
    LSystem::LSystem(std::string axiom_, std::vector<Rule> productions_)
        : axiom_{ axiom_ }
        , context_free_productions_{ productions_ }
    {}

    LSystem::LSystem(std::string axiom_,
                     std::vector<Rule> context_free_productions_,
                     std::vector<Rule> context_sensitive_productions_)
        : axiom_{ axiom_ }
        , context_free_productions_{ context_free_productions_ }
        , context_sensitive_productions_{ context_sensitive_productions_ }
    {}

    LSystem::LSystem(std::string axiom_,
                     std::vector<Rule> context_free_productions_,
                     std::vector<Rule> context_sensitive_productions_,
                     std::string ignore)
        : axiom_{ axiom_ }
        , context_free_productions_{ context_free_productions_ }
        , context_sensitive_productions_{ context_sensitive_productions_ }
        , ignore_{ ignore }
    {}

    std::string LSystem::generate(const int n) const
    {
        std::string state = axiom_;
        for (int i = 0; i < n; i++)
        {
            std::string next_state;
            for (auto it = state.begin(); it < state.end(); it++)
            {
                std::string next_successor(1, *it);
                for (const auto &rule : context_free_productions_)
                    if (rule.get_predecessor() == *it)
                        next_successor = rule.get_successor();

                std::optional<char> left_context = std::nullopt;
                if (it != state.begin())
                {
                    auto left_context_it = std::find_if(
                        std::reverse_iterator(it), state.rend(),
                        [&](char c) {
                            return ignore_.find(c) == std::string::npos;
                        });

                    if (left_context_it != state.rend())
                        left_context = *left_context_it;
                }

                std::optional<char> right_context = std::nullopt;
                if (it != state.end())
                {
                    auto right_context_it =
                        std::find_if(it + 1, state.end(), [&](char c) {
                            return ignore_.find(c) == std::string::npos;
                        });

                    if (right_context_it != state.end())
                        right_context = *right_context_it;
                }

                for (const auto &rule : context_sensitive_productions_)
                    if (rule.get_predecessor() == *it
                        && rule.check_context(left_context, right_context))
                        next_successor = rule.get_successor();
                next_state += next_successor;
            }
            state = next_state;
        }

        return state;
    }
} // namespace core
