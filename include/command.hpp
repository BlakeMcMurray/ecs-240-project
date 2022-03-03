#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <deque>
#include <string>
#include "expression.hpp"
#include "parser.hpp"

namespace BasiK
{
    class Command
    {
    protected:
        std::map<std::string, std::string> parent_vars;
        std::map<std::string, std::string> *scope_vars;
        std::deque<Command> *nested_commands;
        virtual void parse(std::string) = 0;

    public:
        explicit Command(std::map<std::string, std::string> parent_scope_vars, std::map<std::string, std::string> parent_parent_vars = {})
        {
            this->parent_vars.merge(parent_scope_vars);
            this->parent_vars.merge(parent_parent_vars);
            this->scope_vars = new std::map<std::string, std::string>;
            this->nested_commands = new std::deque<Command>;
        }
        ~Command()
        {
            delete this->scope_vars;
            delete this->nested_commands;
        }
    };

    class While : public Command
    {
    private:
        BExp exp;
        void parse(std::string);

    public:
        explicit While(std::string command_text, std::map<std::string, std::string> parent_vars, std::map<std::string, std::string> scope_vars)
            : Command(scope_vars, parent_vars), exp(Parser::parse_bool_exp(command_text)) {}
        ~While() = default;
    };

    class If : public Command
    {
    private:
        BExp exp;
        void parse(std::string);

    public:
        explicit If(std::string command_text, std::map<std::string, std::string> parent_vars, std::map<std::string, std::string> scope_vars)
            : Command(scope_vars, parent_vars), exp(BExp::parse_bool_exp(command_text)) {}
        ~If() = default;
    };

    class For : public Command
    {
    private:
        std::string var_name;
        int start;
        int stop;
        void parse(std::string);

    public:
        explicit For(std::string command_text, std::map<std::string, std::string> parent_vars, std::map<std::string, std::string> scope_vars)
            : Command(scope_vars, parent_vars)
        {
            parse(command_text);
        }
        ~For() = default;
    };

    class Assignment : public Command
    {
    protected:
        std::string var_name;
        virtual void parse(std::string) = 0;

    public:
        explicit Assignment(std::map<std::string, std::string> parent_vars, std::map<std::string, std::string> scope_vars)
            : Command(scope_vars, parent_vars) {}
        ~Assignment() = default;
    };

    class AAssignment : public Assignment
    {
    private:
        void parse(std::string);

    public:
        explicit AAssignment(std::string command_text, std::map<std::string, std::string> parent_vars, std::map<std::string, std::string> scope_vars)
            : Assignment(scope_vars, parent_vars)
        {
            parse(command_text);
        }
        ~AAssignment() = default;
    };

    class BAssignment : public Assignment
    {
    private:
        void parse(std::string);

    public:
        explicit BAssignment(std::string command_text, std::map<std::string, std::string> parent_vars, std::map<std::string, std::string> scope_vars)
            : Assignment(scope_vars, parent_vars)
        {
            parse(command_text);
        }
        ~BAssignment() = default;
    };

} // namespace BasiK

#endif