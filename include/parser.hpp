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
        static std::string parse_bool_exp(std::string);
        static std::string parse_arithmetic_exp(std::string);
    };

    std::string Parser::parse_bool_exp(std::string text)
    {
    }

    std::string Parser::parse_arithmetic_exp(std::string text)
    {
    }
}
#endif