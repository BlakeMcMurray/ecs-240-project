#ifndef COMPLEXCOMMAND_HPP
#define COMPLEXCOMMAND_HPP

#include <map>
#include <string>
#include <deque>
#include <vector>
#include "token.hpp"
#include "command.hpp"
#include "expression.hpp"

namespace BasiK
{
    class ComplexCommand : public Command
    {
    protected:
        // std::unique_ptr<std::deque<BasiK::Command>> nested_commands;
        std::unique_ptr<std::deque<BasiK::Token>> nested_tokens;

    public:
        // explicit ComplexCommand(std::unique_ptr<std::deque<BasiK::Command>> &nested_commands,
        //                         std::map<std::string, std::string> &parent_scope_vars)
        //     : Command(parent_scope_vars)
        // {
        //     this->nested_commands = std::move(nested_commands);
        // }
        explicit ComplexCommand(std::map<std::string, std::string> &parent_scope_vars)
            : Command(parent_scope_vars)
        {
            this->nested_tokens = nullptr;
        }
        ~ComplexCommand() = default;
        void attach_nested_tokens(std::unique_ptr<std::deque<BasiK::Token>> &nested_tokens)
        {
            this->nested_tokens = std::move(nested_tokens);
        }
        std::deque<BasiK::Token> copy_nested_tokens();
    };

    class While : public ComplexCommand
    {
    private:
        std::string exp_raw;
        std::string parse_exp(std::string);

    public:
        explicit While(std::string command_text,
                       std::map<std::string, std::string> &parent_scope_vars)
            : ComplexCommand(parent_scope_vars),
              exp_raw(parse_exp(command_text)) {}
        ~While() = default;
        bool exp_is_true();
    };

    class If : public ComplexCommand
    {
    private:
        std::string exp_raw;
        std::string parse_exp(std::string);

    public:
        explicit If(std::string command_text,
                    std::map<std::string, std::string> &parent_scope_vars)
            : ComplexCommand(parent_scope_vars),
              exp_raw(parse_exp(command_text)) {}
        ~If() = default;
        bool exp_is_true();
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
                     std::map<std::string, std::string> &parent_scope_vars)
            : ComplexCommand(parent_scope_vars),
              var_name(parse_var_name(command_text)),
              crnt_index(parse_start(command_text)),
              stop_index(parse_stop(command_text)) {}
        ~For() = default;
    };
}

#endif