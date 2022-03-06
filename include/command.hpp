#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <deque>
#include <string>
#include <boost/regex.hpp>
#include "expression.hpp"

namespace BasiK
{
    class Command
    {
    public:
        std::map<std::string, std::string> *scope_vars;
        explicit Command(std::map<std::string, std::string> &parent_scope_vars)
            : scope_vars(&parent_scope_vars) {}
        ~Command() = default;
    };

    class If : public Command
    {
    private:
        std::string exp_raw;
        std::string parse_exp(std::string);

    public:
        explicit If(std::string command_text,
                    std::map<std::string, std::string> &parent_scope_vars)
            : Command(parent_scope_vars),
              exp_raw(parse_exp(command_text)) {}
        ~If() = default;
        bool exp_is_true();
    };
} // namespace BasiK

#endif