#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include <map>
#include <string>
#include <deque>
#include "command.hpp"
#include "expression.hpp"

namespace BasiK
{
    class Assignment : public Command
    {
    protected:
        std::string var_name;
        std::string parse_var_name(std::string);

    public:
        explicit Assignment(std::string command_text, std::map<std::string, std::string> &parent_scope_vars)
            : Command(parent_scope_vars),
              var_name(parse_var_name(command_text)) {}
        ~Assignment() = default;
        virtual void execute(std::deque<std::string> &) = 0;
        static std::string parse_exp(std::string);
    };

    class AAssignment : public Assignment
    {
    private:
        AExp exp;

    public:
        explicit AAssignment(std::string command_text, std::map<std::string, std::string> &parent_scope_vars)
            : Assignment(command_text, parent_scope_vars),
              exp(parse_exp(command_text)) {}
        ~AAssignment() = default;
        void execute(std::deque<std::string> &);
    };

    class BAssignment : public Assignment
    {
    private:
        BExp exp;

    public:
        explicit BAssignment(std::string command_text, std::map<std::string, std::string> &parent_scope_vars)
            : Assignment(command_text, parent_scope_vars),
              exp(parse_exp(command_text)) {}
        ~BAssignment() = default;
        void execute(std::deque<std::string> &);
    };
} // namespace BasiK

#endif