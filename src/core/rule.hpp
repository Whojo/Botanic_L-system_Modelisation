#pragma once

#include <optional>
#include <functional>
#include <string>
#include <vector>
#include <memory>


namespace core
{
    using ContextChecker = std::function<bool(std::optional<char>, std::optional<char>)>;

    class Rule
    {
    public:
        Rule(const char predecessor, const std::string successor);
        Rule(const char predecessor, const std::vector<std::string> successors);
        Rule(const char predecessor, const std::string successor,
             const ContextChecker context_checker);
        Rule(const char predecessor, const std::vector<std::string> successors,
             const ContextChecker context_checker);

        char get_predecessor() const;
        std::string get_successor() const;
        bool check_context(std::optional<char> left_context,
                           std::optional<char> right_context) const;

    private:
        const char predecessor_;
        const std::vector<std::string> successors_;
        const ContextChecker context_checker_;
    };
}
