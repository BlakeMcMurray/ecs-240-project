#include <iostream>
#include "tokenizer.hpp"
using namespace boost::algorithm;
using namespace BasiK;

std::string Scanner::getTokenStr(Token token)
{
    std::string formattedToken;
    switch (token.tType)
    {
    case TokenType::whileLoop:
        formattedToken = "whileLoop";
        break;
    case TokenType::forLoop:
        formattedToken = "forLoop\t";
        break;
    case TokenType::ifStatement:
        formattedToken = "ifStatement";
        break;
    case TokenType::assignment:
        formattedToken = "assignment";
        break;
    case TokenType::comment:
        formattedToken = "comment";
        break;
    case TokenType::eof:
        formattedToken = "eof\t";
        break;
    default:
        formattedToken = "error\t";
    }

    formattedToken += "\t\t|";
    formattedToken += token.lineNum;
    formattedToken += "\t\t|";
    formattedToken += token.tabInd;
    formattedToken += "\t\t|";
    formattedToken += token.text;
    formattedToken += "\n";
    return formattedToken;
}

void Scanner::printTokens()
{
    cout << "TokenType\t\t|LineNum\t|TabInd\t\t|Text" << endl;
    cout << "-------------------------------------------------------------------------\n";
    for (size_t i = 0; i < this->tokens->size(); i++)
        cout << getTokenStr(this->tokens->at(i));
}

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

void Scanner::tokenize(deque<string> rawLines)
{
    deque<string> splitted;
    for (size_t i = 0; i < rawLines.size(); i++)
    {
        Token t;
        int tabInd = countTabs(rawLines[i]);
        boost::trim(rawLines[i]);
        string text = rawLines[i];

        if (isComment(rawLines[i]))
            t = Token(TokenType::comment, i + 1, rawLines[i]);
        else if (isWhile(text))
            t = Token(TokenType::whileLoop, i + 1, rawLines[i], tabInd);
        else if (isFor(text))
            t = Token(TokenType::forLoop, i + 1, rawLines[i], tabInd);
        else if (isIf(text))
            t = Token(TokenType::ifStatement, i + 1, rawLines[i], tabInd);
        else if (isAssignment(text))
            t = Token(TokenType::assignment, i + 1, rawLines[i], tabInd);
        else
        {
            t = Token(TokenType::error, i + 1, rawLines[i], tabInd);
            std::cerr << "Error line {" << i + 1 << "} in statement: \"" << text << "\"" << endl;
            exit(1);
        }
        this->tokens->push_back(t);
    }
}

void Scanner::insertEOF(int lineNum)
{
    Token eof = Token(TokenType::eof, lineNum);
    tokens->push_back(eof);
}
