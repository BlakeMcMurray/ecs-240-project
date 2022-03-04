#include <iostream>
#include "program.hpp"
#include "complexCommand.hpp"
#include "assignment.hpp"

void BasiK::Program::evaluate_tokens(std::deque<Token> tokens)
{
    get_nested(tokens, 0);
}

std::unique_ptr<std::deque<BasiK::Command>> BasiK::Program::get_nested(std::deque<Token> tokens, int crnt_tab_index)
{
    if (tokens.front().tType == BasiK::TokenType::eof)
        return nullptr;

    auto commands = std::unique_ptr<std::deque<BasiK::Command>>(new std::deque<BasiK::Command>());
    std::unique_ptr<std::deque<BasiK::Command>> nested_cmds = nullptr;
    while (!tokens.empty())
    {
        BasiK::Token t = tokens.front();
        tokens.pop_front();

        if (t.tabInd != crnt_tab_index && commands->empty())
            tab_index_error(t, crnt_tab_index);
        else if (t.tabInd < crnt_tab_index)
            return commands;

        switch (t.tType)
        {
        case TokenType::whileLoop:
        {
            nested_cmds = get_nested(tokens, crnt_tab_index + 1);
            While whileCmd(t.text, nested_cmds, this->scope_vars);
            commands->push_back(whileCmd);
            break;
        }
        case TokenType::forLoop:
        {
            nested_cmds = get_nested(tokens, crnt_tab_index + 1);
            For forCmd(t.text, nested_cmds, this->scope_vars);
            commands->push_back(forCmd);
            break;
        }
        case TokenType::ifStatement:
        {
            nested_cmds = get_nested(tokens, crnt_tab_index + 1);
            If ifCmd(t.text, nested_cmds, this->scope_vars);
            commands->push_back(ifCmd);
            break;
        }
        case TokenType::assignment:
        {
            std::string assignmentType = Expression::parse_expression_type(Assignment::parse_exp(t.text));
            if (assignmentType.compare("AExp"))
            {
                AAssignment aAss(t.text, this->scope_vars);
                commands->push_back(aAss);
            }
            else
            {
                BAssignment bAss(t.text, this->scope_vars);
                commands->push_back(bAss);
            }
            break;
        }
        }
    }
    return commands;
}

void BasiK::Program::tab_index_error(BasiK::Token t, int last_tab_index)
{
    std::cerr << "Error line {" << t.lineNum << "} in statement: \"" << t.text << "\"" << endl;
    std::cerr << "The command following a Complex Command must have exactly one more tab then the Complex Command preceding it."
              << "but it has a difference of {" << t.tabInd - last_tab_index << "} tabs instead." << endl;
    exit(1);
}