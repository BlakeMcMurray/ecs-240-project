#include "command.hpp"
#include <iostream>

std::string BasiK::If::parse_exp(std::string command_text)
{
    boost::regex re{"(?<=if).*(?=do)"};
    boost::smatch match;
    boost::regex_search(command_text, match, re);
    return match.str();
}

bool BasiK::If::exp_is_true()
{
    return BasiK::BExp::evaluate_bool_exp(this->exp_raw, *this->scope_vars);
}

std::string BasiK::Print::parse_var_name(std::string command_text)
{
    boost::regex re{"(?<=print).*"};
    boost::smatch match;
    boost::regex_search(command_text, match, re);
    return match.str();
}

void BasiK::Print::execute()
{
    try
    {
        std::cout << this->var_name << " is " << this->scope_vars->at(this->var_name) << std::endl;
    }
    catch (const std::exception &e)
    {
        BasiK::ExpressionError::var_doesnt_exist_error(this->var_name);
    }
}