#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <unordered_set>
#include <string>
#include "boost/algorithm/string.hpp"

namespace BasiK
{
    // Expression Base Class
    class Expression
    {
    public:
        static char parse_expression_type(std::string);
    };

    // Arithmetic Expression
    class AExp : public Expression
    {
    private:
        // Verify there are no logical or binary comparitors in an arthmetic expressions
        static bool verify(std::string);

    public:
        static const std::unordered_set<std::string> operators;
        // Return string integer
        static int evaluate(std::string, std::map<std::string, std::string> *);
    };

    // Boolean Expression
    class BExp : public Expression
    {
    private:
        // Verify only a single binary comparator between arithmetic expressions
        //  and only a single logical comparator between boolean expressions
        static bool verify(std::string);

    public:
        static const std::unordered_set<std::string> logicalComparators;
        static const std::unordered_set<std::string> binaryComparators;
        // Return string boolean ("TRUE" or "FALSE")
        static bool evaluate(std::string, std::map<std::string, std::string> *);
    };
}

#endif