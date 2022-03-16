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
        std::shared_ptr<std::map<std::string, std::string>> scope_vars;
        explicit Command(std::shared_ptr<std::map<std::string, std::string>> parent_scope_vars)
            : scope_vars(parent_scope_vars) {}
        ~Command() = default;
    };

    class If : public Command
    {
    private:
        std::string exp_raw;
        std::string parse_exp(std::string);

    public:
        explicit If(std::string command_text,
                    std::shared_ptr<std::map<std::string, std::string>> parent_scope_vars)
            : Command(parent_scope_vars),
              exp_raw(parse_exp(command_text)) {}
        ~If() = default;
        bool exp_is_true();
    };

    class Print : public Command
    {
    private:
        std::string var_name;
        std::string parse_var_name(std::string);
        void execute();

    public:
        explicit Print(std::string command_text,
                       std::shared_ptr<std::map<std::string, std::string>> parent_scope_vars)
            : Command(parent_scope_vars),
              var_name(parse_var_name(command_text))
        {
            execute();
        }
        ~Print() = default;
    };
} // namespace BasiK

#endif