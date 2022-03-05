#include "complexCommand.hpp"

std::deque<BasiK::Token> BasiK::ComplexCommand::copy_nested_tokens()
{
    std::deque<BasiK::Token> nested_tokens_copy(this->nested_tokens->begin(), this->nested_tokens->end());
    return nested_tokens_copy;
}

std::string BasiK::While::parse_exp(std::string command_text)
{
    // TODO
    return command_text;
}

bool BasiK::While::exp_is_true()
{
    return BasiK::BExp::evaluate(this->exp_raw, this->scope_vars);
}

std::string BasiK::If::parse_exp(std::string command_text)
{
    // TODO
    return command_text;
}

bool BasiK::If::exp_is_true()
{
    return BasiK::BExp::evaluate(this->exp_raw, this->scope_vars);
}

std::string BasiK::For::parse_var_name(std::string command_text)
{
    // TODO
    return command_text;
}

int BasiK::For::parse_start(std::string command_text)
{
    // TODO
    return 0;
}

int BasiK::For::parse_stop(std::string command_text)
{
    // TODO
    return 0;
}