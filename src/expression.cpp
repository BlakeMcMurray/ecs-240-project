#include "expression.hpp"

/**************************
 * Expression Base
 **************************/

char BasiK::Expression::parse_expression_type(std::string exp_text)
{
    return BasiK::BExp::verify_correct_exp(exp_text) ? 'B' : 'A';
}

std::deque<BasiK::ExpressionToken> BasiK::Expression::tokenize_expression(std::string exp_text)
{
    std::stringstream ss(exp_text);
    std::deque<BasiK::ExpressionToken> tokens;

    BasiK::ExpressionToken t;
    std::string crnt_token_text;
    int num_from_stream;
    bool crnt_token_evaluated = false;
    while (ss.peek() != EOF)
    {
        // Stream Number
        if (std::isdigit(ss.peek()) ||
            (ss.peek() == '-' &&
             (tokens.empty() || tokens.back().type == ExpTokenType::OPERATOR)))
        {
            ss >> num_from_stream;
            crnt_token_text = std::to_string(num_from_stream);
            t.type = ExpTokenType::NUM;
            crnt_token_evaluated = true;
        }
        else
        {
            // TODO Handle Parenthesis
            crnt_token_text += ss.get();
            if (AExp::operators.contains(crnt_token_text))
            {
                t.type = ExpTokenType::OPERATOR;
                crnt_token_evaluated = true;
            }
            else if (BExp::logicalComparators.contains(crnt_token_text))
            {
                t.type = ExpTokenType::LOGICAL_COMPARATOR;
                crnt_token_evaluated = true;
            }
            else if (BExp::binaryComparators.contains(crnt_token_text))
            {
                t.type = ExpTokenType::BINARY_COMPARATOR;
                crnt_token_evaluated = true;
            }

            if (crnt_token_evaluated)
            {
                t.text = crnt_token_text;
                tokens.push_back(t);
                crnt_token_text.clear();
                crnt_token_evaluated = false;
            }
        }
    }
}

/**************************
 * Arithmetic Expression
 **************************/

const std::unordered_set<std::string> BasiK::AExp::operators = {"+", "-", "*", "/"};

bool BasiK::AExp::verify_correct_exp(std::string exp_text)
{
    return !BasiK::BExp::verify_correct_exp(exp_text);
}

int BasiK::AExp::evaluate(std::string exp, std::map<std::string, std::string> *vars)
{
    // TODO
    return 1;
}

/**************************
 * Boolean Expression
 **************************/

const std::unordered_set<std::string> BasiK::BExp::logicalComparators = {"and", "or", "not"};
const std::unordered_set<std::string> BasiK::BExp::binaryComparators = {"==", "!=", "<", "<=", ">", ">="};

bool BasiK::BExp::verify_correct_exp(std::string exp_text)
{
    for (auto op : BasiK::BExp::logicalComparators)
        if (exp_text.find(op) != std::string::npos)
            return true;
    for (auto op : BasiK::BExp::binaryComparators)
        if (exp_text.find(op) != std::string::npos)
            return true;
    return false;
}

bool BasiK::BExp::evaluate(std::string exp, std::map<std::string, std::string> *vars)
{
    // TODO
    return true;
}