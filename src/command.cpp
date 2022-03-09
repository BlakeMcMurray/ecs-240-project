#include "command.hpp"

std::string BasiK::If::parse_exp(std::string command_text)
{
    boost::regex re{"(?<=if).*(?=do)"};
    boost::smatch match;
    boost::regex_search(command_text, match, re);
    return match.str();
}

bool BasiK::If::exp_is_true()
{
    return BasiK::BExp::evaluate_bool_exp(this->exp_raw, this->scope_vars);
}