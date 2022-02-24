#include "tokenizer.hpp"
using namespace boost::algorithm;
using namespace BasiK;

// input: text, output: true or false
bool Scanner::isNumber(string text)
{
    cout << text << endl;
    std::regex re(R"((-?[1-9]\d*(\.\d+)?)|-0\.\d+|0(\.\d+)?)");
    return (std::regex_match(text, re));
}

// std::regex to match variables
// I think a simple way to make sure we don't use keywords, is
// to check keywords before checking if its a variable'
// Ideally the std::regex would perfectly map allowed variables to the output
// true and any thing that is not an allowed variable would be mapped to false
bool Scanner::isVariable(string text)
{
    regex re(R"(([a-z]|[A-Z]|_)+(\d|[a-z]|[A-Z]|_)*)");
    return (regex_match(text, re));
}

bool Scanner::isComparitor(string text)
{
    bool b = (text == "==") || (text == "!=") || (text == "<") || (text == ">") || (text == "<=") || (text == ">=");
    return (b);
}

// not implemented
bool Scanner::isIf(string text)
{
    bool b = text == "if";
    return (b);
}

// this will apply to individual lines, not
// space delimited strings
bool Scanner::isComment(string text)
{
    return (text[0] == '#');
}

// not implemented
bool Scanner::isWhile(string text)
{

    bool b = text == "while";
    return (b);
}

bool Scanner::isFor(string text)
{
    bool b = text == "for";
    return (b);
}

bool Scanner::isBool(string text)
{
    bool b = (text == "true" || text == "false");
    return (b);
}

bool Scanner::isFrom(string text)
{
    bool b = (text == "from");
    return (b);
}

bool Scanner::isTo(string text)
{
    bool b = (text == "to");
    return (b);
}

bool Scanner::isOperator(string text)
{
    bool b = (text == "+" | text == "-" | text == "/" | text == "*" | text == "**" | text == "log");
    return (b);
}

bool Scanner::isEqual(string text)
{
    bool b = text == "=";
    return (b);
}

// function to check if word is reserved
bool Scanner::isReserved(string text)
{
    return (isBool(text) | isFor(text) | isWhile(text) | isIf(text) | isFrom(text) | isTo(text));
}

vector<string> Scanner::toRawLines(ifstream &ifile)
{
    // vector to contain each raw line of text
    vector<string> rawLines;

    // generates the lines
    string line;
    while (getline(ifile, line))
    {

        regex re(R"(\S)");
        if (regex_search(line, re))
        {
            trim(line);
            rawLines.push_back(line);
        }
    }

    return rawLines;
}

void Scanner::scan(vector<string> rawLines)
{
    vector<string> splitted;
    for (int i = 0; i < rawLines.size(); i++)
    {
        // It will make it easier if comments can only be done
        // as individual lines
        if (isComment(rawLines[i]))
        {
            Token t;
            t.tType = "comment";
            t.text = rawLines[i];
            continue;
        }

        // splits a string into a vector of strings by space delimiter
        boost::split(splitted, rawLines[i], boost::is_any_of(" "));
        for (int j = 0; j < splitted.size(); j++)
        {
            Token t;
            string text = splitted[j];

            if (isBool(text))
            {
                // assign token value and add it to the tokens vector
                t.tType = "bool";
                t.text = text;
                this->tokens->push_back(t);
            }
            else if (isComparitor(text))
            {
                // assign token value and add it to the tokens vector
                t.tType = "comparitor";
                t.text = text;
                this->tokens->push_back(t);
            }
            else if (isEqual(text))
            {
                // assign token value and add it to the tokens vector
                t.tType = "equal";
                t.text = text;
                this->tokens->push_back(t);
            }

            else if (isIf(text))
            {
                // assign token value and add it to the tokens vector
                t.tType = "if";
                t.text = text;
                this->tokens->push_back(t);
            }

            else if (isOperator(text))
            {
                // assign token value and add it to the tokens vector
                t.tType = "operator";
                t.text = text;
                this->tokens->push_back(t);
            }
            else if (isWhile(text))
            {
                // assign token value and add it to the tokens vector
                t.tType = "while";
                t.text = text;
                this->tokens->push_back(t);
            }
            else if (isFor(text))
            {
                // assign token value and add it to the tokens vector
                t.tType = "for";
                t.text = text;
                this->tokens->push_back(t);
            }

            else if (isOperator(text))
            {
                // assign token value and add it to the tokens vector
                t.tType = "operator";
                t.text = text;
                this->tokens->push_back(t);
            }

            else if (isNumber(text))
            {
                t.tType = "number";
                t.text = text;
                this->tokens->push_back(t);
            }
            else if (isVariable(text))
            {
                t.tType = "var";
                t.text = text;
                this->tokens->push_back(t);
            }

            else
            {
                /*
                What was typed is not a token, should do further analysis
                to decipher what the student typed in.  Might be cool to use a deep learning
                model to try to guess what the student is trying to write, and provide
                an example written in BasiK.
                */
                cout << "not a token: error" << endl;
                cout << "The text is: " << text << endl;
                return;
            }
        }
    }

    for (int i = 0; i < this->tokens->size(); i++)
    {
        cout << this->tokens->at(i).text << " is a " << this->tokens->at(i).tType << endl;
    }
}
// Object used for determining token names
// we probably don't actuall need this, but just in case
/*
class TokenNames {
  public:
    TokenNames() {
        unordered_map<string, bool> tNames;
        tNames.insert(make_pair("comparitor", false));
        tNames.insert(make_pair("variable",false));
        tNames.insert(make_pair("number", false));
        tNames.insert(make_pair("for", false));
        tNames.insert(make_pair("while", false));
        tNames.insert(make_pair("if", false));
        tNames.insert(make_pair("comment", false));
    };
};*/
