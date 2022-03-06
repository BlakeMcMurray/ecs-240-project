#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <deque>
#include <string>
#include "expression.hpp"

namespace BasiK
{
    class Command
    {
    protected:
        std::deque<Command> *nested_commands;

    public:
        std::map<std::string, std::string> parent_vars;
        std::map<std::string, std::string> scope_vars;
        explicit Command(std::deque<Command> nested_commands,
                         std::map<std::string, std::string> parent_scope_vars,
                         std::map<std::string, std::string> parent_parent_vars = {})
            : nested_commands(&nested_commands)
        {
            this->parent_vars.insert(parent_scope_vars.begin(), parent_scope_vars.end());
            this->parent_vars.insert(parent_parent_vars.begin(), parent_parent_vars.end());
        }
        ~Command() = default;
    };

    class While : public Command
    {
    private:
        BExp exp;
        std::string parse_exp(std::string);

    public:
        explicit While(std::string command_text,
                       std::deque<Command> nested_commands,
                       std::map<std::string, std::string> parent_scope_vars,
                       std::map<std::string, std::string> parent_parent_vars = {})
            : Command(nested_commands, parent_scope_vars, parent_parent_vars),
              exp(parse_exp(command_text)) {}
        ~While() = default;
    };

    class If : public Command
    {
    private:
        BExp exp;
        std::string parse_exp(std::string);

    public:
        explicit If(std::string command_text,
                    std::deque<Command> nested_commands,
                    std::map<std::string, std::string> parent_scope_vars,
                    std::map<std::string, std::string> parent_parent_vars = {})
            : Command(nested_commands, parent_scope_vars, parent_parent_vars),
              exp(parse_exp(command_text)) {}
        ~If() = default;
    };

    class For : public Command
    {
    private:
        std::string var_name;
        int crnt_count;
        int stop_count;
        std::string parse_var_name(std::string);
        int parse_start(std::string);
        int parse_stop(std::string);

    public:
        explicit For(std::string command_text,
                     std::deque<Command> nested_commands,
                     std::map<std::string, std::string> parent_scope_vars,
                     std::map<std::string, std::string> parent_parent_vars = {})
            : Command(nested_commands, parent_scope_vars, parent_parent_vars),
              var_name(parse_var_name(command_text)),
              crnt_count(parse_start(command_text)),
              stop_count(parse_stop(command_text)) {}
        ~For() = default;
    };
} // namespace BasiK

#endif