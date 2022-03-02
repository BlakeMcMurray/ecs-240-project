#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace BasiK
{
    enum TokenType
    {
        whileLoop,
        forLoop,
        ifStatement,
        assignment,
        comment,
        eof,
        error
        // ifElseStatement,
    };

    // token object that holds the type of token,
    // the position in the original text and the
    // raw text that the token consists of
    class Token
    {
    public:
        TokenType tType;
        int lineNum;
        int tabInd;
        std::string text;
        Token() = default;
        Token(TokenType tType, int lineNum, std::string text = "", int tabInd = 0)
        {
            this->tType = tType;
            this->lineNum = lineNum;
            this->tabInd = tabInd;
            this->text = text;
        }
    };
}

#endif