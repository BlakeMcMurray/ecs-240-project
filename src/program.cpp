#include <iostream>
#include "program.hpp"
#include "complexCommand.hpp"
#include "assignment.hpp"

std::unique_ptr<std::deque<BasiK::Line>> BasiK::Program::evaluate_lines(std::deque<Line> &lines, int active_tab_index)
{
    if (lines.front().type == LINE_TYPE::END_OF_FILE)
        return nullptr;

    bool neverTrue;
    BasiK::Line line;
    auto crnt_lines = std::unique_ptr<std::deque<BasiK::Line>>(new std::deque<BasiK::Line>());
    std::unique_ptr<std::deque<BasiK::Line>> nested_lines = nullptr;
    while (!lines.empty())
    {
        neverTrue = true;
        if (lines.front().tabInd < active_tab_index)
            return crnt_lines;

        line = lines.front();
        lines.pop_front();
        crnt_lines->push_back(line);

        if (line.tabInd != active_tab_index && crnt_lines->empty())
            tab_index_error(line, active_tab_index);

        switch (line.type)
        {
        case LINE_TYPE::WHILE:
        {
            BasiK::While whileCmd(line.text, this->scope_vars);
            if (whileCmd.exp_is_true())
            {
                neverTrue = false;
                nested_lines = evaluate_lines(lines, active_tab_index + 1);
                whileCmd.attach_nested_lines(nested_lines);
                while (whileCmd.exp_is_true())
                {
                    auto copy_nested_lines = whileCmd.copy_nested_lines();
                    evaluate_lines(copy_nested_lines, active_tab_index + 1);
                }
            }
            if (neverTrue)
                skip_nested_lines(lines, active_tab_index);
            break;
        }
        case LINE_TYPE::FOR:
        {
            BasiK::For forCmd(line.text, this->scope_vars);
            if (forCmd.exp_is_true())
            {
                neverTrue = false;
                nested_lines = evaluate_lines(lines, active_tab_index + 1);
                forCmd.attach_nested_lines(nested_lines);
                forCmd.increment();
                while (forCmd.exp_is_true())
                {
                    auto copy_nested_lines = forCmd.copy_nested_lines();
                    evaluate_lines(copy_nested_lines, active_tab_index + 1);
                    forCmd.increment();
                }
            }
            if (neverTrue)
                skip_nested_lines(lines, active_tab_index);
            break;
        }
        case LINE_TYPE::IF:
        {
            BasiK::If ifCmd(line.text, this->scope_vars);
            if (ifCmd.exp_is_true())
            {
                neverTrue = false;
                evaluate_lines(lines, active_tab_index + 1);
            }
            if (neverTrue)
                skip_nested_lines(lines, active_tab_index);
            break;
        }
        case LINE_TYPE::ASSIGNMENT:
        {
            if (Expression::parse_expression_type(Assignment::parse_exp(line.text)) == 'A')
                BasiK::AAssignment aAss(line.text, this->scope_vars);
            else
                BasiK::BAssignment bAss(line.text, this->scope_vars);
        }
        }
    }
    return crnt_lines;
}

void BasiK::Program::skip_nested_lines(std::deque<Line> &lines, int crnt_tab_index)
{
    while (lines.front().tabInd > crnt_tab_index)
    {
        lines.pop_front();
    }
}

// Error handling
void BasiK::Program::tab_index_error(BasiK::Line line, int last_tab_index)
{
    std::cerr << "Error line {" << line.lineNum << "} in statement: \"" << line.text << "\"" << endl;
    std::cerr << "The command following a Complex Command must have exactly one more tab then the Complex Command preceding it."
              << "but it has a difference of {" << line.tabInd - last_tab_index << "} tabs instead." << endl;
    exit(1);
}