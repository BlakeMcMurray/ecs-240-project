#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <map>
#include <deque>
#include <string>
#include "command.hpp"
#include "tokenizer.hpp"

namespace BasiK
{
    class Program
    {
    private:
        std::map<std::string, std::string> scope_vars;
        std::deque<std::string> output;
        void evaluate_tokens(std::deque<Token>);
        std::unique_ptr<std::deque<BasiK::Command>> get_nested(std::deque<Token>, int);

    public:
        Program(std::deque<Token> tokens)
            evaluate_tokens(tokens);
        ~Program() = default;
        void execute_commands();
        std::string output_to_str();
        void output_to_file(std::string);

        void tab_index_error(BasiK::Token, int);
    };
}

#endif