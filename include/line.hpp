#ifndef LINE_HPP
#define LINE_HPP

#include <string>

enum LINE_TYPE
{
    WHILE,
    FOR,
    IF,
    ASSIGNMENT,
    COMMENT,
    END_OF_FILE,
    ERROR
};

namespace BasiK
{
    // line object that holds the type of line,
    // the position in the original text and the
    // raw text that the line consists of
    class Line
    {
    public:
        LINE_TYPE type;
        int lineNum;
        int tabInd;
        std::string text;
        Line() = default;
        Line(LINE_TYPE type, int lineNum, std::string text = "", int tabInd = 0)
        {
            this->type = type;
            this->lineNum = lineNum;
            this->tabInd = tabInd;
            this->text = text;
        }
    };
}

#endif