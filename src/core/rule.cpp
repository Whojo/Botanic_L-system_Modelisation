#include "rule.hpp"

namespace core
{

    Rule::Rule(const char predecessor, const std::string successor)
        : predecessor_{predecessor}, successor_{successor}
    {}

    char Rule::get_predecessor() const
    {
        return predecessor_;
    }

    std::string Rule::get_successor() const
    {
        return successor_;
    }
}
