#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <map>
#include <deque>
#include <string>
#include "token.hpp"
#include "command.hpp"
#include "scanner.hpp"

namespace BasiK
{
    class Program
    {
    private:
        std::map<std::string, std::string> scope_vars;
        std::deque<std::string> output;
        std::unique_ptr<std::deque<BasiK::Token>> evaluate_tokens(std::deque<Token>, int);
        void skip_nested(std::deque<Token> &, int);

    public:
        Program(std::deque<Token> tokens)
        {
            evaluate_tokens(tokens, 0);
        }
        ~Program() = default;
        // void execute_commands();
        // std::string output_to_str();
        // void output_to_file(std::string);
        // void pretty_print_commands(std::unique_ptr<std::deque<BasiK::Command>> &);

        // Error handling
        void tab_index_error(BasiK::Token, int);
    };
}

#endif