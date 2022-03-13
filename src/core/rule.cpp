#include "rule.hpp"

#include  <random>


namespace
{
    std::string select_randomly(const std::vector<std::string> &vect)
    {
        return vect[std::rand() % vect.size()];
    }
} // namespace

namespace core
{
    Rule::Rule(const char predecessor, std::vector<std::string> successors)
        : predecessor_{predecessor}, successors_{successors}
    {}

    Rule::Rule(const char predecessor, std::string successor)
        : predecessor_{predecessor}, successors_{successor}
    {}

    char Rule::get_predecessor() const
    {
        return predecessor_;
    }

    std::string Rule::get_successor() const
    {
        return select_randomly(successors_);
    }
}
