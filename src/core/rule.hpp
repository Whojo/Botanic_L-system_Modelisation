#pragma once

#include <string>
#include <vector>
#include <memory>


namespace core
{
    class Rule
    {
    public:
        Rule(const char predecessor, const std::string successor);
        Rule(const char predecessor, const std::vector<std::string> successors);

        char get_predecessor() const;
        std::string get_successor() const;

    private:
        const char predecessor_;
        const std::vector<std::string> successors_;
    };
}
