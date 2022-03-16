#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <map>
#include <deque>
#include <string>
#include "line.hpp"
#include "command.hpp"
#include "scanner.hpp"

namespace BasiK
{
    class Program
    {
    private:
        std::shared_ptr<std::map<std::string, std::string>> global_vars;
        std::deque<std::string> output;
        std::unique_ptr<std::deque<BasiK::Line>> evaluate_lines(std::deque<Line> &, int);
        std::unique_ptr<std::deque<BasiK::Line>> get_nested_lines(std::deque<Line> &, int);
        void skip_nested_lines(std::deque<Line> &, int);

    public:
        Program(std::deque<Line> lines)
        {
            global_vars = std::make_shared<std::map<std::string, std::string>>();
            evaluate_lines(lines, 0);
        }
        ~Program() = default;
        // std::string output_to_str();
        // void output_to_file(std::string);
        // void pretty_print_commands(std::unique_ptr<std::deque<BasiK::Command>> &);

        // Error handling
        void tab_index_error(BasiK::Line, int);
    };
}

#endif