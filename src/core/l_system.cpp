#include "l_system.hpp"

#include <algorithm>


namespace core
{
    namespace
    {
        std::optional<State> apply_rules(const std::vector<Rule> &rules, const Module &pred,
                                         const State &left, const State &right)
        {
            for (const auto &rule : rules)
            {
                const std::optional<State> &possible_succ = rule.apply(pred, left, right);
                if (possible_succ.has_value())
                    return *possible_succ;
            }

            return std::nullopt;
        }

        template<class Iterator>
        State get_context(const Iterator &begin, const Iterator &end, const std::string &ignore)
        {
            std::vector<Module> modules;
            std::copy_if(begin, end, std::back_inserter(modules), [&](const Module &mod) {
                return ignore.find(mod.letter) == std::string::npos;
            });

            return modules;
        }
    }

    LSystem::LSystem(const State &axiom_, const std::vector<Rule> &productions_)
        : axiom_{ axiom_ }
        , context_free_productions_{ productions_ }
    {}

    LSystem::LSystem(const State &axiom_,
                     const std::vector<Rule> &context_free_productions_,
                     const std::vector<Rule> &context_sensitive_productions_)
        : axiom_{ axiom_ }
        , context_free_productions_{ context_free_productions_ }
        , context_sensitive_productions_{ context_sensitive_productions_ }
    {}

    LSystem::LSystem(const State &axiom_,
                     const std::vector<Rule> &context_free_productions_,
                     const std::vector<Rule> &context_sensitive_productions_,
                     const std::string &ignore)
        : axiom_{ axiom_ }
        , context_free_productions_{ context_free_productions_ }
        , context_sensitive_productions_{ context_sensitive_productions_ }
        , ignore_{ ignore }
    {}

    State LSystem::generate(const int n) const
    {
        State state = axiom_;
        for (int i = 0; i < n; i++)
        {
            const auto &modules = state.get_modules();
            State next_state;
            for (auto it = modules.begin(); it < modules.end(); it++)
            {
                const State &cont_free_succ = apply_rules(context_free_productions_,
                                                          *it, {}, {}).value_or(State({*it}));

                const State &left  = get_context(modules.begin(), it, ignore_);
                const State &right = get_context(it,   modules.end(), ignore_);

                next_state += apply_rules(context_sensitive_productions_,
                                          *it, left, right).value_or(cont_free_succ);
            }
            state = next_state;
        }

        return state;
    }
} // namespace core
