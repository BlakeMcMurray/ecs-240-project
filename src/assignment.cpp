#include "assignment.hpp"
#include <iostream>

std::string BasiK::Assignment::parse_exp(std::string command_text)
{
    return command_text.substr(command_text.find_first_of('=') + 1);
}

std::string BasiK::Assignment::parse_var_name(std::string command_text)
{
    return command_text.substr(command_text.find_first_of('t') + 1, command_text.find_first_of('='));
}

void BasiK::AAssignment::execute()
{
    this->scope_vars->insert(std::pair<std::string, std::string>(
        this->var_name,
        std::to_string(BasiK::AExp::evaluate(this->exp_raw, this->scope_vars))));
}

void BasiK::BAssignment::execute()
{
    this->scope_vars->insert(std::pair<std::string, std::string>(
        this->var_name,
        BasiK::BExp::evaluate(this->exp_raw, this->scope_vars) ? "TRUE" : "FALSE"));
}