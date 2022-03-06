#include <iostream>
#include "program.hpp"
#include "complexCommand.hpp"
#include "assignment.hpp"

std::unique_ptr<std::deque<BasiK::Line>> BasiK::Program::evaluate_lines(std::deque<Line> &lines, int active_tab_index)
{
    if (lines.front().L_Type == BasiK::LINE_TYPE::EOF_LINE)
        return nullptr;

    bool neverTrue;
    BasiK::Line t;
    auto crnt_lines = std::unique_ptr<std::deque<BasiK::Line>>(new std::deque<BasiK::Line>());
    std::unique_ptr<std::deque<BasiK::Line>> nested_lines = nullptr;
    while (!lines.empty())
    {
        neverTrue = true;
        if (lines.front().tabInd < active_tab_index)
            return crnt_lines;

        t = lines.front();
        lines.pop_front();
        crnt_lines->push_back(t);

        if (t.tabInd != active_tab_index && crnt_lines->empty())
            tab_index_error(t, active_tab_index);

        switch (t.L_Type)
        {
        case LINE_TYPE::WHILE_LINE:
        {
            BasiK::While whileCmd(t.text, this->scope_vars);
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
        case LINE_TYPE::FOR_LINE:
        {
            BasiK::For forCmd(t.text, this->scope_vars);
            if (forCmd.exp_is_true())
            {
                neverTrue = false;
                nested_lines = evaluate_lines(lines, active_tab_index + 1);
                forCmd.attach_nested_lines(nested_lines);
                while (forCmd.exp_is_true())
                {
                    auto copy_nested_lines = forCmd.copy_nested_lines();
                    evaluate_lines(copy_nested_lines, active_tab_index + 1);
                }
            }
            if (neverTrue)
                skip_nested_lines(lines, active_tab_index);
            break;
        }
        case LINE_TYPE::IF_LINE:
        {
            BasiK::If ifCmd(t.text, this->scope_vars);
            if (ifCmd.exp_is_true())
            {
                neverTrue = false;
                evaluate_lines(lines, active_tab_index + 1);
            }
            if (neverTrue)
                skip_nested_lines(lines, active_tab_index);
            break;
        }
        case LINE_TYPE::ASSIGNMENT_LINE:
        {
            switch (Expression::parse_expression_type(Assignment::parse_exp(t.text)))
            {
            case 'A':
            {
                BasiK::AAssignment aAss(t.text, this->scope_vars);
                break;
            }
            case 'B':
                BasiK::BAssignment bAss(t.text, this->scope_vars);
            }
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
void BasiK::Program::tab_index_error(BasiK::Line t, int last_tab_index)
{
    std::cerr << "Error line {" << t.lineNum << "} in statement: \"" << t.text << "\"" << endl;
    std::cerr << "The command following a Complex Command must have exactly one more tab then the Complex Command preceding it."
              << "but it has a difference of {" << t.tabInd - last_tab_index << "} tabs instead." << endl;
    exit(1);
}