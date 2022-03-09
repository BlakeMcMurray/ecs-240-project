#include "assignment.hpp"

/**************************
 * Assignment Base
 **************************/

std::string BasiK::Assignment::parse_exp(std::string command_text)
{
    return command_text.substr(command_text.find_first_of('=') + 1);
}

std::string BasiK::Assignment::parse_var_name(std::string command_text)
{
    boost::regex re{"(?<=let).*(?==)"};
    boost::smatch match;
    boost::regex_search(command_text, match, re);
    return match.str();
}

/**************************
 * Arithmetic Assignment
 **************************/

void BasiK::AAssignment::execute()
{
    this->scope_vars->insert(std::pair<std::string, std::string>(
        this->var_name,
        std::to_string(BasiK::AExp::evaluate_arithmetic_exp(this->exp_raw, this->scope_vars))));
}

/**************************
 * Boolean Assignment
 **************************/

void BasiK::BAssignment::execute()
{
    this->scope_vars->insert(std::pair<std::string, std::string>(
        this->var_name,
        BasiK::BExp::evaluate_bool_exp(this->exp_raw, this->scope_vars) ? "TRUE" : "FALSE"));
}