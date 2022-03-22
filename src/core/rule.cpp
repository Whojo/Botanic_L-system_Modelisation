#include "rule.hpp"

#include <random>


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
        : predecessor_{predecessor}, successors_{successors},
          context_checker_{[](ostr, ostr) { return true;}}
    {}

    Rule::Rule(const char predecessor, std::string successor)
        : predecessor_{predecessor}, successors_{successor},
          context_checker_{[](ostr, ostr) { return true;}}
    {}

    Rule::Rule(const char predecessor, std::vector<std::string> successors,
               const ContextChecker context_checker)
        : predecessor_{ predecessor }
        , successors_{ successors }
        , context_checker_{ context_checker }
    {}

    Rule::Rule(const char predecessor, std::string successor,
               const ContextChecker context_checker)
        : predecessor_{ predecessor }
        , successors_{ successor }
        , context_checker_{ context_checker }
    {}

    char Rule::get_predecessor() const
    {
        return predecessor_;
    }

    std::string Rule::get_successor() const
    {
        return select_randomly(successors_);
    }

    bool Rule::check_context(cstr &left_context,
                             cstr &right_context) const
    {
        return context_checker_(left_context, right_context);
    }
} // namespace core
