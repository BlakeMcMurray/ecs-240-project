#ifndef LINE_HPP
#define LINE_HPP

#include <string>

namespace BasiK
{
    enum LINE_TYPE
    {
        WHILE_LINE,
        FOR_LINE,
        IF_LINE,
        ASSIGNMENT_LINE,
        COMMENT_LINE,
        EOF_LINE,
        ERROR_LINE
    };

    // line object that holds the type of line,
    // the position in the original text and the
    // raw text that the line consists of
    class Line
    {
    public:
        LINE_TYPE L_Type;
        int lineNum;
        int tabInd;
        std::string text;
        Line() = default;
        Line(LINE_TYPE L_Type, int lineNum, std::string text = "", int tabInd = 0)
        {
            this->L_Type = L_Type;
            this->lineNum = lineNum;
            this->tabInd = tabInd;
            this->text = text;
        }
    };
}

#endif