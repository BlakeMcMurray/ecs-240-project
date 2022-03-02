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

    public:
        explicit Command()
        {
            this->scope_vars = new std::map<std::string, std::string>;
            this->nested_commands = new std::deque<Command>;
        }
        explicit Command(std::map<std::string, std::string> parent_vars, std::map<std::string, std::string> scope_vars)
        {
            this->parent_vars.merge(parent_vars);
            this->parent_vars.merge(scope_vars);
            this->scope_vars = new std::map<std::string, std::string>;
            this->nested_commands = new std::deque<Command>;
        }
        ~Command()
        {
            delete this->scope_vars;
            delete this->nested_commands;
        }
    };

    class SingleBExp : public Command
    {
    private:
        BExp exp;

    public:
        explicit SingleBExp(std::string command_text, std::map<std::string, std::string> parent_vars, std::map<std::string, std::string> scope_vars)
            : Command(parent_vars, scope_vars), exp(Parser::parse_bool_exp(command_text)) {}
        ~SingleBExp();
    };

} // namespace BasiK

#endif