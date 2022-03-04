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
    public:
        std::map<std::string, std::string> *scope_vars;
        explicit Command(std::map<std::string, std::string> &parent_scope_vars)
            : scope_vars(&parent_scope_vars) {}
        ~Command() = default;
    };
} // namespace BasiK

#endif