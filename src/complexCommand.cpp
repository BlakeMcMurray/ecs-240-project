#include "complexCommand.hpp"

/**************************
 * Complex Command Base
 **************************/

std::deque<BasiK::Line> BasiK::ComplexCommand::copy_nested_lines()
{
    std::deque<BasiK::Line> nested_lines_copy(this->nested_lines->begin(), this->nested_lines->end());
    return nested_lines_copy;
}

/**************************
 * While Command
 **************************/

std::string BasiK::While::parse_exp(std::string command_text)
{
    boost::regex re{"(?<=while).*(?=do)"};
    boost::smatch match;
    boost::regex_search(command_text, match, re);
    return match.str();
}

bool BasiK::While::exp_is_true()
{
    return BasiK::BExp::evaluate_bool_exp(this->exp_raw, this->scope_vars);
}

/**************************
 * For Command
 **************************/

std::string BasiK::For::parse_var_name(std::string command_text)
{
    boost::regex re{"(?<=for).*(?=from)"};
    boost::smatch match;
    boost::regex_search(command_text, match, re);
    return match.str();
}

int BasiK::For::parse_start(std::string command_text)
{
    boost::regex re{"(?<=from).*(?=to)"};
    boost::smatch match;
    boost::regex_search(command_text, match, re);
    return std::stoi(match.str());
}

int BasiK::For::parse_stop(std::string command_text)
{
    boost::regex re{"(?<=to).*(?=do)"};
    boost::smatch match;
    boost::regex_search(command_text, match, re);
    return std::stoi(match.str());
}

int BasiK::For::increment()
{
    this->scope_vars->at(this->var_name) = std::to_string(++this->crnt_count);
    return this->crnt_count;
}

bool BasiK::For::exp_is_true()
{
    // TODO Should I handle this with boolean expression interpreter instead?
    return this->crnt_count < this->stop_count;
}