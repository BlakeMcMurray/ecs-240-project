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
    LOGICAL_COMPARATOR,
    BINARY_COMPARATOR,
    EXP
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
    protected:
        static std::deque<ExpressionToken> tokenize_expression(std::string);

    public:
        // Return a string representing the types of expression. Either "AExp" or "BExp".
        static char parse_expression_type(std::string);
    };

    class ExpressionError : Expression
    {
    public:
        static void wrong_expression_type(std::string, std::string, std::string);
        static void parenthesis_error(std::string);
        static void aexp_token_error(ExpressionToken);
        static void var_doesnt_exist_error(ExpressionToken);
    };

    // Arithmetic Expression
    class AExp : public Expression
    {
    private:
        static int evaluate_term(std::deque<BasiK::ExpressionToken> &, std::map<std::string, std::string> *);
        static int evaluate_factor(std::deque<BasiK::ExpressionToken> &, std::map<std::string, std::string> *);

    public:
        static const std::unordered_set<std::string> operators;
        // Verify there are no logical or binary comparitors in an arthmetic expressions
        static bool verify_correct_exp(std::string);
        // Return string integer
        static int evaluate_arithmetic_exp(std::string, std::map<std::string, std::string> *);
    };

    // Boolean Expression
    class BExp : public Expression
    {
    public:
        static const std::unordered_set<std::string> logicalComparators;
        static const std::unordered_set<std::string> binaryComparators;
        // Verify only a single binary comparator between arithmetic expressions and only a single logical comparator between boolean expressions
        static bool verify_correct_exp(std::string);
        // Return string boolean ("TRUE" or "FALSE")
        static bool evaluate_bool_exp(std::string, std::map<std::string, std::string> *);
    };
}

#endif