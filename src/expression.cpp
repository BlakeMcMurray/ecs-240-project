#include "expression.hpp"

// Return a string representing the types of expression. Either "AExp" or "BExp".
std::string BasiK::Expression::parse_expression_type(std::string text)
{
    return text;
}

// Evaluate the  value of the arithmetic expression represented by the text passed to constructor.
void BasiK::AExp::evaluate()
{
}

std::string BasiK::AExp::parse_arithmetic_exp(std::string text)
{
    return text;
}

// Evaluate the value of the boolean expression represented by the text passed to constructor.
void BasiK::BExp::evaluate()
{
}

std::string BasiK::BExp::parse_bool_exp(std::string text)
{
    return text;
}