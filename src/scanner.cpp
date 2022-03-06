#include <iostream>
#include "scanner.hpp"
using namespace boost::algorithm;
using namespace BasiK;

deque<string> Scanner::toRawLines(ifstream &ifile)
{
    // vector to contain each raw line of text
    deque<string> rawLines;

    // generates the lines
    string line;
    while (getline(ifile, line))
    {
        regex re(R"(^(?!\s*$).+)");
        if (regex_search(line, re))
        {
            // trim(line);
            // TODO: There is definitely a better way to do this, but doing this for sake of time.
            boost::replace_all(line, "\t", "    ");
            rawLines.push_back(line);
        }
    }

    ifile.close();
    return rawLines;
}

bool Scanner::isWhile(string command)
{
    regex re(R"(^(while)\s+([a-zA-Z_]\w*){1}\s+((do){1}\s*)$)");
    return regex_search(command, re);
}

bool Scanner::isFor(string command)
{
    regex re(R"(^(for)\s+([a-zA-Z]\w*){1}\s+(from)\s+\d+\s+(to)\s+\d+\s+((do){1}\s*)$)");
    return regex_search(command, re);
}

bool Scanner::isIf(string command)
{
    regex re(R"(^(if)\s+([a-zA-Z_]\w*){1}\s+((do){1}\s*)$)");
    return regex_search(command, re);
}

bool Scanner::isAssignment(string command)
{
    regex re(R"(^(let)\s+([a-zA-Z_]\w*){1}(\s)+={1}\s+([a-zA-Z_]\w*\s*$|-?(\d+\s*)$|(\S)+\s*)+)");
    return regex_search(command, re);
}

// this will apply to individual lines, not
// space delimited strings
bool Scanner::isComment(string text)
{
    return (text[0] == '#');
}

int Scanner::countTabs(string text)
{
    int occurrences = 0;
    std::string::size_type pos = 0;
    std::string target = "    ";
    while ((pos = text.find(target, pos)) < text.find_first_not_of(" "))
    {
        occurrences++;
        pos += target.length();
    }
    return occurrences;
}

void Scanner::scan(deque<string> rawLines)
{
    deque<string> splitted;
    for (size_t i = 0; i < rawLines.size(); i++)
    {
        Line t;
        int tabInd = countTabs(rawLines[i]);
        boost::trim(rawLines[i]);
        string formatted_text = remove_spaces(rawLines[i]);

        if (isComment(rawLines[i]))
            t = Line(LINE_TYPE::COMMENT_LINE, i + 1, formatted_text);
        else if (isWhile(rawLines[i]))
            t = Line(LINE_TYPE::WHILE_LINE, i + 1, formatted_text, tabInd);
        else if (isFor(rawLines[i]))
            t = Line(LINE_TYPE::FOR_LINE, i + 1, formatted_text, tabInd);
        else if (isIf(rawLines[i]))
            t = Line(LINE_TYPE::IF_LINE, i + 1, formatted_text, tabInd);
        else if (isAssignment(rawLines[i]))
            t = Line(LINE_TYPE::ASSIGNMENT_LINE, i + 1, formatted_text, tabInd);
        else
        {
            t = Line(LINE_TYPE::ERROR_LINE, i + 1, formatted_text, tabInd);
            std::cerr << "Error line {" << i + 1 << "} in statement: \"" << rawLines[i] << "\"" << endl;
            exit(1);
        }
        this->lines->push_back(t);
    }
}

void Scanner::insertEOF(int lineNum)
{
    Line eof = Line(LINE_TYPE::EOF_LINE, lineNum);
    lines->push_back(eof);
}

std::string Scanner::get_formatted_line(Line line)
{
    std::string formattedLine;
    switch (line.L_Type)
    {
    case LINE_TYPE::WHILE_LINE:
        formattedLine = "whileLoop";
        break;
    case LINE_TYPE::FOR_LINE:
        formattedLine = "forLoop\t";
        break;
    case LINE_TYPE::IF_LINE:
        formattedLine = "ifStatement";
        break;
    case LINE_TYPE::ASSIGNMENT_LINE:
        formattedLine = "assignment";
        break;
    case LINE_TYPE::COMMENT_LINE:
        formattedLine = "comment";
        break;
    case LINE_TYPE::EOF_LINE:
        formattedLine = "eof\t";
        break;
    default:
        formattedLine = "error\t";
    }

    formattedLine += "\t\t|";
    formattedLine += std::to_string(line.lineNum);
    formattedLine += "\t\t|";
    formattedLine += std::to_string(line.tabInd);
    formattedLine += "\t\t|";
    formattedLine += line.text;
    formattedLine += "\n";
    return formattedLine;
}

void Scanner::print_lines()
{
    cout << "LINE_TYPE\t\t|LineNum\t|TabInd\t\t|Text" << endl;
    cout << "-------------------------------------------------------------------------\n";
    for (size_t i = 0; i < this->lines->size(); i++)
        cout << get_formatted_line(this->lines->at(i));
}

std::string Scanner::remove_spaces(std::string str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}