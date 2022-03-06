#ifndef COMPLEXCOMMAND_HPP
#define COMPLEXCOMMAND_HPP

#include <map>
#include <string>
#include <deque>
#include <vector>
#include "line.hpp"
#include "command.hpp"
#include "expression.hpp"

namespace BasiK
{
    class ComplexCommand : public Command
    {
    protected:
        std::unique_ptr<std::deque<BasiK::Line>> nested_lines;

    public:
        explicit ComplexCommand(std::map<std::string, std::string> &parent_scope_vars)
            : Command(parent_scope_vars)
        {
            this->nested_lines = nullptr;
        }
        ~ComplexCommand() = default;
        void attach_nested_lines(std::unique_ptr<std::deque<BasiK::Line>> &nested_lines)
        {
            this->nested_lines = std::move(nested_lines);
        }
        std::deque<BasiK::Line> copy_nested_lines();
        virtual bool exp_is_true() = 0;
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

    class For : public ComplexCommand
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
                     std::map<std::string, std::string> &parent_scope_vars)
            : ComplexCommand(parent_scope_vars),
              var_name(parse_var_name(command_text)),
              crnt_count(parse_start(command_text)),
              stop_count(parse_stop(command_text))
        {
            this->scope_vars->insert_or_assign(this->var_name, std::to_string(this->crnt_count));
        }
        ~For() = default;
        int increment();
        bool exp_is_true();
    };
}

#endif