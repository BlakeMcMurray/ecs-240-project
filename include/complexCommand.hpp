#ifndef COMPLEXCOMMAND_HPP
#define COMPLEXCOMMAND_HPP

#include <map>
#include <string>
#include <deque>
#include "command.hpp"
#include "expression.hpp"

namespace BasiK
{
    class ComplexCommand : public Command
    {
    protected:
        std::unique_ptr<std::deque<BasiK::Command>> nested_commands;

    public:
        explicit ComplexCommand(std::unique_ptr<std::deque<BasiK::Command>> &nested_commands,
                                std::map<std::string, std::string> &parent_scope_vars)
            : Command(parent_scope_vars)
        {
            this->nested_commands = std::move(nested_commands);
        }
        ~ComplexCommand() = default;
    };

    class While : public ComplexCommand
    {
    private:
        BExp exp;
        std::string parse_exp(std::string);

    public:
        explicit While(std::string command_text,
                       std::unique_ptr<std::deque<BasiK::Command>> &nested_commands,
                       std::map<std::string, std::string> &parent_scope_vars)
            : ComplexCommand(nested_commands, parent_scope_vars),
              exp(parse_exp(command_text)) {}
        ~While() = default;
    };

    class If : public ComplexCommand
    {
    private:
        BExp exp;
        std::string parse_exp(std::string);

    public:
        explicit If(std::string command_text,
                    std::unique_ptr<std::deque<BasiK::Command>> &nested_commands,
                    std::map<std::string, std::string> &parent_scope_vars)
            : ComplexCommand(nested_commands, parent_scope_vars),
              exp(parse_exp(command_text)) {}
        ~If() = default;
    };

    class For : public ComplexCommand
    {
    private:
        std::string var_name;
        int crnt_index;
        int stop_index;
        std::string parse_var_name(std::string);
        int parse_start(std::string);
        int parse_stop(std::string);

    public:
        explicit For(std::string command_text,
                     std::unique_ptr<std::deque<BasiK::Command>> &nested_commands,
                     std::map<std::string, std::string> &parent_scope_vars)
            : ComplexCommand(nested_commands, parent_scope_vars),
              var_name(parse_var_name(command_text)),
              crnt_index(parse_start(command_text)),
              stop_index(parse_stop(command_text)) {}
        ~For() = default;
    };
}

#endif