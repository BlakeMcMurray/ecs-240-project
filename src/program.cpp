#include <iostream>
#include "program.hpp"
#include "complexCommand.hpp"
#include "assignment.hpp"

std::unique_ptr<std::deque<BasiK::Token>> BasiK::Program::evaluate_tokens(std::deque<Token> tokens, int active_tab_index)
{
    if (tokens.front().tType == BasiK::TokenType::eof)
        return nullptr;

    auto crnt_tokens = std::unique_ptr<std::deque<BasiK::Token>>(new std::deque<BasiK::Token>());
    std::unique_ptr<std::deque<BasiK::Token>> nested_tokens = nullptr;
    bool neverTrue = true;
    while (!tokens.empty())
    {
        if (tokens.front().tabInd < active_tab_index)
            return crnt_tokens;

        BasiK::Token t = tokens.front();
        tokens.pop_front();
        crnt_tokens->push_back(t);

        if (t.tabInd != active_tab_index && crnt_tokens->empty())
            tab_index_error(t, active_tab_index);

        switch (t.tType)
        {
        case TokenType::whileLoop:
        {
            BasiK::While whileCmd(t.text, this->scope_vars);
            if (whileCmd.exp_is_true())
            {
                neverTrue = false;
                nested_tokens = evaluate_tokens(tokens, active_tab_index + 1);
                whileCmd.attach_nested_tokens(nested_tokens);
                while (whileCmd.exp_is_true())
                {
                    auto copy_nested_tokens = whileCmd.copy_nested_tokens();
                    evaluate_tokens(copy_nested_tokens, active_tab_index + 1);
                }
            }
            if (neverTrue)
                skip_nested(tokens, active_tab_index);
            break;
        }
        case TokenType::forLoop:
        {
            break;
        }
        case TokenType::ifStatement:
        {
            BasiK::If ifCmd(t.text, this->scope_vars);
            if (ifCmd.exp_is_true())
            {
                neverTrue = false;
                evaluate_tokens(tokens, active_tab_index + 1);
                // ifCmd.attach_nested_tokens(nested_tokens);
                // auto copy_nested_tokens = ifCmd.copy_nested_tokens();
                // parse_nested(copy_nested_tokens, active_tab_index + 1);
            }
            if (neverTrue)
                skip_nested(tokens, active_tab_index);
            break;
        }
        case TokenType::assignment:
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
    return crnt_tokens;
}

void BasiK::Program::skip_nested(std::deque<Token> &tokens, int crnt_tab_index)
{
    while (tokens.front().tabInd > crnt_tab_index)
    {
        tokens.pop_front();
    }
}

// Error handling
void BasiK::Program::tab_index_error(BasiK::Token t, int last_tab_index)
{
    std::cerr << "Error line {" << t.lineNum << "} in statement: \"" << t.text << "\"" << endl;
    std::cerr << "The command following a Complex Command must have exactly one more tab then the Complex Command preceding it."
              << "but it has a difference of {" << t.tabInd - last_tab_index << "} tabs instead." << endl;
    exit(1);
}