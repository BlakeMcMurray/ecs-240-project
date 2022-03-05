#include "expression.hpp"

// Return a string representing the types of expression. Either "AExp" or "BExp".
char BasiK::Expression::parse_expression_type(std::string exp_text)
{
    for (auto op : BasiK::AExp::operators)
        if (exp_text.find(op))
            return 'A';
    return 'B';
}

// Arithmetic Expression
const std::unordered_set<std::string> BasiK::AExp::operators = {"+", "-", "*", "/"};

bool BasiK::AExp::verify(std::string)
{
    // TODO
    return true;
}

int BasiK::AExp::evaluate(std::string exp, std::map<std::string, std::string> *vars)
{
    // TODO
    return 1;
}

// Boolean Expression
const std::unordered_set<std::string> BasiK::BExp::logicalComparators = {"and", "or", "not"};
const std::unordered_set<std::string> BasiK::BExp::binaryComparators = {"==", "!=", "<", "<=", ">", ">="};

bool BasiK::BExp::verify(std::string)
{
    // TODO
    return true;
}

bool BasiK::BExp::evaluate(std::string exp, std::map<std::string, std::string> *vars)
{
    // TODO
    return true;
}