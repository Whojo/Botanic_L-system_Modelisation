#include "l_system.hpp"
#include "utils.hpp"

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

                int index = it - state.begin();
                int end_index = state.length() - index;
                std::string left_context = state.substr(0, (index < 0) ? 0:index);
                std::string right_context = state.substr(index, end_index);

                ignore_chars(left_context, ignore_);
                ignore_chars(right_context, ignore_);

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
