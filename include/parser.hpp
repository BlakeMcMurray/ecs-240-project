#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <string>
#include <deque>

namespace BasiK
{
    class Parser
    {
    public:
        // ALL OF THESE WERE MOVED TO THE EXPRESSION CLASSES
        static std::string get_expression_type(std::string text);
        static std::string parse_bool_exp(std::string);
        static std::string parse_arithmetic_exp(std::string);
    };
}
#endif