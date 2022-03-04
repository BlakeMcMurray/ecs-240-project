#include "expression.hpp"

// Return a string representing the types of expression. Either "AExp" or "BExp".
std::string BasiK::Expression::parse_expression_type(std::string text)
{
    return text;
}

// Arithmetic Expression
const std::unordered_set<std::string> BasiK::AExp::operators = {"+", "-", "*", "/"};

// Evaluate the  value of the arithmetic expression represented by the text passed to constructor.
void BasiK::AExp::evaluate()
{
}

void BasiK::AExp::reevaluate(std::string)
{
}

std::string BasiK::AExp::parse_arithmetic_exp(std::string text)
{
    return text;
}

// Boolean Expression
const std::unordered_set<std::string> BasiK::BExp::logicalComparators = {"and", "or", "not"};
const std::unordered_set<std::string> BasiK::BExp::binaryComparators = {"==", "!=", "<", "<=", ">", ">="};

// Evaluate the value of the boolean expression represented by the text passed to constructor.
void BasiK::BExp::evaluate()
{
}

void BasiK::BExp::reevaluate(std::string)
{
}

std::string BasiK::BExp::parse_bool_exp(std::string text)
{
    return text;
}