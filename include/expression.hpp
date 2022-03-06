#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <unordered_set>
#include <string>
#include <deque>
#include <sstream>
#include <boost/regex.hpp>

enum ExpTokenType
{
    NUM,
    VAR,
    BOOL,
    OPERATOR,
    LOGICAL_COMPARATOR,
    BINARY_COMPARATOR,
    AEXP,
    BEXP
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
        static char parse_expression_type(std::string);
        static std::deque<ExpressionToken> tokenize_expression(std::string);
    };

    // Arithmetic Expression
    class AExp : public Expression
    {
    public:
        static const std::unordered_set<std::string> operators;
        // Verify there are no logical or binary comparitors in an arthmetic expressions
        static bool verify_correct_exp(std::string);
        // Return string integer
        static int evaluate(std::string, std::map<std::string, std::string> *);
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
        static bool evaluate(std::string, std::map<std::string, std::string> *);
    };
}

#endif