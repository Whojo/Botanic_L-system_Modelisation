#include "l_system.hpp"


namespace core
{
    LSystem::LSystem(std::string axiom_, std::vector<Rule> productions_)
        : axiom_{axiom_}, productions_{productions_}
    {}

    std::string LSystem::generate(const int n) const
    {
        std::string state = axiom_;
        for (int i = 0; i < n; i++)
        {
            std::string next_state;
            for (const auto &c : state)
                for (const auto &rule : productions_)
                    if (rule.get_predecessor() == c)
                        next_state += rule.get_successor();
            state = next_state;
        }

        return state;
    }
}
