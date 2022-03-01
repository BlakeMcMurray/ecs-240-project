#include "tokenizer.hpp"
using namespace boost::algorithm;
using namespace BasiK;

void Scanner::printToken(Token token)
{
    switch (token.tType)
    {
    case TokenType::whileLoop:
        cout << "whileLoop";
        break;
    case TokenType::forLoop:
        cout << "forLoop\t";
        break;
    case TokenType::ifStatement:
        cout << "ifStatement";
        break;
    case TokenType::assignment:
        cout << "assignment";
        break;
    case TokenType::comment:
        cout << "comment";
        break;
    case TokenType::eof:
        cout << "eof\t";
        break;
    default:
        cout << "error\t";
    }

    cout << "\t\t|" << token.lineNum << "\t\t|" << token.tabInd << "\t\t|" << token.text << endl;
}

void Scanner::printTokens()
{
    cout << "TokenType\t\t|LineNum\t|TabInd\t\t|Text" << endl;
    cout << "-------------------------------------------------------------------------\n";
    for (size_t i = 0; i < this->tokens->size(); i++)
        printToken(this->tokens->at(i));
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
            boost::replace_all(line, "\t", "    ");
            rawLines.push_back(line);
        }
    }

    ifile.close();
    return rawLines;
}

bool Scanner::isWhile(string expressionTerm)
{
    return (expressionTerm == "while");
}

bool Scanner::verifyWhile(string command)
{
    regex re(R"(^(while)\s+([a-zA-Z_]\w*){1}\s+((do){1}\s*)$)");
    return regex_search(command, re);
}

bool Scanner::isFor(string expressionTerm)
{
    return (expressionTerm == "for");
}

bool Scanner::verifyFor(string command)
{
    regex re(R"(^(for)\s+([a-zA-Z]\w*){1}\s+(from)\s+\d+\s+(to)\s+\d+\s+((do){1}\s*)$)");
    return regex_search(command, re);
}

bool Scanner::isIf(string expressionTerm)
{
    return (expressionTerm == "if");
}

bool Scanner::verifyIf(string command)
{
    regex re(R"(^(if)\s+([a-zA-Z_]\w*){1}\s+((do){1}\s*)$)");
    return regex_search(command, re);
}

bool Scanner::isAssignment(string expressionTerm)
{
    return (expressionTerm == "let");
}

bool Scanner::verifyAssignment(string command)
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

void Scanner::insertEOF(int lineNum)
{
    Token eof = Token(TokenType::eof, lineNum);
    tokens->push_back(eof);
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
        // splits a string into a vector of strings by space delimiter
        Token t;
        int tabInd = countTabs(rawLines[i]);
        boost::split(splitted, rawLines[i], boost::is_any_of(" "));
        string expressionTerm = splitted[4 * tabInd];
        boost::trim(rawLines[i]);
        string text = rawLines[i];

        if (isComment(rawLines[i]))
        {
            t = Token(TokenType::comment, i + 1, rawLines[i]);
        }
        else if (isWhile(expressionTerm) && verifyWhile(text))
        {
            t = Token(TokenType::whileLoop, i + 1, rawLines[i], tabInd);
        }
        else if (isFor(expressionTerm) && verifyFor(text))
        {
            t = Token(TokenType::forLoop, i + 1, rawLines[i], tabInd);
        }
        else if (isIf(expressionTerm) && verifyIf(text))
        {
            t = Token(TokenType::ifStatement, i + 1, rawLines[i], tabInd);
        }
        else if (isAssignment(expressionTerm) && verifyAssignment(text))
        {
            t = Token(TokenType::assignment, i + 1, rawLines[i], tabInd);
        }
        else
        {
            t = Token(TokenType::error, i + 1, rawLines[i], tabInd);
            cout << "Error: not a token" << endl;
            cout << "The text is: " << text << endl;
            // exit(1);
        }
        this->tokens->push_back(t);
    }
    insertEOF(rawLines.size() + 1);
}
