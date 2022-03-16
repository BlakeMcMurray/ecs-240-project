#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <unordered_set>
#include <string>
#include <deque>
#include <sstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

enum ExpTokenType
{
    NUM,
    VAR,
    BOOL,
    ADD_SUB,
    MULT_DIV,
    NOT,
    LOGICAL_COMPARATOR,
    BINARY_COMPARATOR,
    EXP,
    AEXP
};

namespace BasiK
{
    class ExpressionToken
    {
    public:
        ExpTokenType type;
        std::string text;
    };

    // Expression Base Class
    class Expression
    {
    public:
        // Return a string representing the types of expression. Either "AExp" or "BExp".
        static char parse_expression_type(const std::string&, std::map<std::string, std::string>);
    };

    // Arithmetic Expression
    class AExp : public Expression
    {
    private:
        static int evaluate_term(std::deque<BasiK::ExpressionToken> &, const std::map<std::string, std::string>&);
        static int evaluate_factor(std::deque<BasiK::ExpressionToken> &, std::map<std::string, std::string>);
        static std::deque<ExpressionToken> tokenize_arithmetic_exp(const std::string&);

    public:
        static const std::unordered_set<std::string> operators;
        static bool verify_correct_exp(const std::string&, std::map<std::string, std::string>);
        static int evaluate_arithmetic_exp(const std::string&, const std::map<std::string, std::string>&);
    };

    // Boolean Expression
    class BExp : public Expression
    {
    private:
        static bool evaluate_boolean(std::deque<BasiK::ExpressionToken> &, std::map<std::string, std::string>);
        static bool evaluate_arithmetic_comparison(const std::string&, const std::string&, const std::string&, const std::map<std::string, std::string>&);
        static std::deque<ExpressionToken> tokenize_boolean_exp(std::string);

    public:
        static const std::unordered_set<std::string> logicalComparators;
        static const std::unordered_set<std::string> binaryComparators;
        static bool verify_correct_exp(const std::string&, std::map<std::string, std::string>);
        static bool evaluate_bool_exp(const std::string&, const std::map<std::string, std::string>&);
    };

    // Expression Error
    class ExpressionError
    {
    public:
        static void wrong_expression_type(const std::string&, const std::string&, const std::string&);
        static void parenthesis_error(const std::string&);
        static void exp_token_error(const ExpressionToken&);
        static void bin_comparison_error(const std::string&, const std::string&, const std::string&);
        static void var_doesnt_exist_error(const std::string&);
    };
}

#endif