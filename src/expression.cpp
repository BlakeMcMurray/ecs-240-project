#include "expression.hpp"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>

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
    char c = ss.get();
    while (c != EOF)
    {
        // Stream Number
        if (crnt_token_text.length() == 0 &&
            (std::isdigit(c) ||
             (c == '-' && (tokens.empty() || tokens.back().type == ExpTokenType::ADD_SUB || tokens.back().type == ExpTokenType::MULT_DIV))))
        {
            ss.unget();
            ss >> num_from_stream;
            crnt_token_text = std::to_string(num_from_stream);
            t.type = ExpTokenType::NUM;
            crnt_token_evaluated = true;
        }
        // Stream expression nested in parenthesis
        else if (c == '(')
        {
            int paren_count = 1;
            while (paren_count != 0)
            {
                c = ss.get();
                if (c == EOF)
                    ExpressionError::parenthesis_error(exp_text);
                else if (c == '(')
                    paren_count++;
                else if (c == ')')
                    paren_count--;
                crnt_token_text += c;
            }
            t.type = ExpTokenType::EXP;
            crnt_token_text.pop_back();
            crnt_token_evaluated = true;
        }
        // Stream Operator
        else if (AExp::operators.contains(std::string(1, c)))
        {
            if (crnt_token_text.length() > 0)
            {
                t.type = ExpTokenType::VAR;
                t.text = crnt_token_text;
                tokens.push_back(t);
                crnt_token_text.clear();
            }
            crnt_token_text += c;

            if (c == '+' || c == '-')
                t.type = ExpTokenType::ADD_SUB;
            else
                t.type = ExpTokenType::MULT_DIV;
            crnt_token_evaluated = true;
        }
        // Stream Logical Comparator
        else if (BExp::logicalComparators.contains(std::string(1, c)))
        {
            if (crnt_token_text.length() > 0)
            {
                t.type = ExpTokenType::VAR;
                t.text = crnt_token_text;
                tokens.push_back(t);
                crnt_token_text.clear();
            }
            crnt_token_text += c;

            t.type = ExpTokenType::LOGICAL_COMPARATOR;
            crnt_token_evaluated = true;
            if (c == '!' && ss.peek() == '=')
            {
                t.type = ExpTokenType::BINARY_COMPARATOR;
                crnt_token_text += ss.get();
            }
        }
        // Stream Binary Comparator
        else if (BExp::binaryComparators.contains(std::string(1, c)))
        {
            if (crnt_token_text.length() > 0)
            {
                t.type = ExpTokenType::VAR;
                t.text = crnt_token_text;
                tokens.push_back(t);
                crnt_token_text.clear();
            }
            crnt_token_text += c;

            t.type = ExpTokenType::BINARY_COMPARATOR;
            crnt_token_evaluated = true;
            if ((c == '<' || c == '>') && ss.peek() == '=')
                crnt_token_text += ss.get();
        }
        else
        {
            crnt_token_text += c;
            // Stream Variable Name or Boolean Literal
            if (crnt_token_text.length() > 2)
            {
                t.type = ExpTokenType::VAR;
                while (std::isalnum(ss.peek()))
                    crnt_token_text += ss.get();

                // TODO Should I store the values as 0/1 or TRUE/FALSE ??
                if (!crnt_token_text.compare("TRUE"))
                {
                    t.type = ExpTokenType::BOOL;
                    // crnt_token_text = "1";
                }
                else if (!crnt_token_text.compare("FALSE"))
                {
                    t.type = ExpTokenType::BOOL;
                    // crnt_token_text = "0";
                }
                crnt_token_evaluated = true;
            }
        }

        if (crnt_token_evaluated)
        {
            t.text = crnt_token_text;
            tokens.push_back(t);
            crnt_token_text.clear();
            crnt_token_evaluated = false;
        }
        c = ss.get();
    }
    return tokens;
}

/**************************
 * Expression Error
 **************************/

void BasiK::ExpressionError::wrong_expression_type(std::string exp_text, std::string expected_type, std::string actual_type)
{
    std::cerr << "Incorrect Expression Error! In Expression: " << exp_text << std::endl;
    std::cerr << "Expected Expression Type: " << expected_type << std::endl;
    std::cerr << "Was Expression Type: " << actual_type << std::endl;
    exit(1);
}

void BasiK::ExpressionError::parenthesis_error(std::string exp_text)
{
    std::cerr << "Unmatched Parenthesis Error!\nIn Expression: ";
    std::cerr << exp_text << std::endl;
    exit(1);
}

void BasiK::ExpressionError::aexp_token_error(ExpressionToken t)
{
    std::cerr << "Token Error!\n";
    std::cerr << t.type << std::endl;
    std::cerr << t.text << std::endl;
    exit(1);
}

void BasiK::ExpressionError::var_doesnt_exist_error(ExpressionToken t)
{
    std::cerr << "Variable doesnt exist!\n";
    std::cerr << t.text << std::endl;
    exit(1);
}

/**************************
 * Arithmetic Expression
 **************************/

const std::unordered_set<std::string> BasiK::AExp::operators = {"+", "-", "*", "/"};

bool BasiK::AExp::verify_correct_exp(std::string exp_text)
{
    return !BasiK::BExp::verify_correct_exp(exp_text);
}

int BasiK::AExp::evaluate_arithmetic_exp(std::string exp, std::map<std::string, std::string> *vars)
{
    if (!verify_correct_exp(exp))
        ExpressionError::wrong_expression_type(exp, "Arithmetic", "Boolean");

    auto tokens = tokenize_expression(exp);
    BasiK::ExpressionToken t;
    int total = evaluate_term(tokens, vars);
    while (!tokens.empty())
    {
        t = tokens.front();
        tokens.pop_front();
        switch (t.type)
        {
        case ExpTokenType::ADD_SUB:
        {
            if (!t.text.compare("+"))
                total += evaluate_term(tokens, vars);
            else
                total -= evaluate_term(tokens, vars);
            break;
        }
        }
    }
    return total;
}

int BasiK::AExp::evaluate_term(std::deque<BasiK::ExpressionToken> &tokens, std::map<std::string, std::string> *vars)
{
    int factor = evaluate_factor(tokens, vars);
    ExpressionToken t = tokens.front();
    switch (t.type)
    {
    case ExpTokenType::MULT_DIV:
    {
        tokens.pop_front();
        if (!t.text.compare("*"))
            return factor * evaluate_factor(tokens, vars);
        else
            return factor / evaluate_factor(tokens, vars);
        break;
    }
    default:
    {
        return factor;
    }
    }
}

int BasiK::AExp::evaluate_factor(std::deque<BasiK::ExpressionToken> &tokens, std::map<std::string, std::string> *vars)
{
    ExpressionToken t = tokens.front();
    tokens.pop_front();
    switch (t.type)
    {
    case ExpTokenType::EXP:
    {
        return evaluate_arithmetic_exp(t.text, vars);
    }
    case ExpTokenType::VAR:
    {
        try
        {
            t.text = vars->at(t.text);
        }
        catch (const std::exception &e)
        {
            ExpressionError::var_doesnt_exist_error(t);
        }
    }
    case ExpTokenType::NUM:
    {
        return std::stoi(t.text);
    }
    default:
    {
        ExpressionError::aexp_token_error(t);
    }
    }
}

/**************************
 * Boolean Expression
 **************************/

const std::unordered_set<std::string> BasiK::BExp::logicalComparators = {"&&", "||", "!"};
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

bool BasiK::BExp::evaluate_bool_exp(std::string exp, std::map<std::string, std::string> *vars)
{
    if (!verify_correct_exp(exp))
        ExpressionError::wrong_expression_type(exp, "Boolean", "Arithmetic");
    return true;
}