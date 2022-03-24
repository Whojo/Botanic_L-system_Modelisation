#pragma once
#include <optional>
#include <functional>
#include <string>
#include <vector>
#include <memory>


using oc = std::optional<char>;
using ostr = std::optional<std::string>;
using cstr = const std::string;

namespace core
{
    using ContextChecker = std::function<bool(const std::string,const std::string)>;

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

        bool check_context(const std::string &left_context, const std::string &right_context) const;

    private:
        const char predecessor_;
        const std::vector<std::string> successors_;
        const ContextChecker context_checker_;
    };
}
