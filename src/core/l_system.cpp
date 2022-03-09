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
            {
                std::string next_successor(1, c);
                for (const auto &rule : productions_)
                    if (rule.get_predecessor() == c)
                        next_successor = rule.get_successor();
                next_state += next_successor;
            }    
            state = next_state;
        }

        return state;
    }
}
