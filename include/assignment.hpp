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
        std::string exp_raw;

    public:
        explicit Assignment(std::string command_text,
                            std::map<std::string, std::string> &parent_scope_vars)
            : Command(parent_scope_vars),
              var_name(parse_var_name(command_text)),
              exp_raw(parse_exp(command_text)) {}
        ~Assignment() = default;
        virtual void execute() = 0;

        static std::string parse_exp(std::string);
        static std::string parse_var_name(std::string);
    };

    class AAssignment : public Assignment
    {
    public:
        explicit AAssignment(std::string command_text,
                             std::map<std::string, std::string> &parent_scope_vars)
            : Assignment(command_text, parent_scope_vars)
        {
            execute();
        }
        ~AAssignment() = default;
        void execute();
    };

    class BAssignment : public Assignment
    {
    public:
        explicit BAssignment(std::string command_text,
                             std::map<std::string, std::string> &parent_scope_vars)
            : Assignment(command_text, parent_scope_vars)
        {
            execute();
        }
        ~BAssignment() = default;
        void execute();
    };
} // namespace BasiK

#endif