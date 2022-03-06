#pragma once

#include <string>


namespace core
{
    class Rule
    {
    public:
        Rule(const char predecessor, const std::string successor);

        char get_predecessor() const;
        std::string get_successor() const;

    private:
        const char predecessor_;
        const std::string successor_;
    };
}
