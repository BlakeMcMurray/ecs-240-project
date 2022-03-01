#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <unordered_map>
#include <regex>
#include "boost/algorithm/string.hpp"
using std::cout;
using std::deque;
using std::endl;
using std::ifstream;
using std::make_pair;
using std::regex;
using std::regex_match;
using std::string;
using std::unordered_map;
using namespace boost::algorithm;

namespace BasiK
{
    // reserved words to check while tokenizing
    class ReservedWords
    {
    public:
        ReservedWords()
        {
            unordered_map<string, bool> rWords;
            rWords.insert(make_pair("for", false));
            rWords.insert(make_pair("if", false));
            rWords.insert(make_pair("from", false));
            rWords.insert(make_pair("while", false));
            rWords.insert(make_pair("do", false));
            rWords.insert(make_pair("int", false));
        };
    };

    // unsure if we need a tokenizer object, but it is here
    // just in case
    class Tokenizer
    {
    public:
        int myNum;
        string myString;
    };

    // token object that holds the type of token,
    // the position in the original text and the
    // raw text that the token consists of
    class Token
    {
    public:
        string tType;
        int sPos;
        string text;
    };

    class Scanner
    {
    public:
        Scanner(ifstream &ifile)
        {
            this->tokens = new deque<Token>();
            tokenize(toRawLines(ifile));
        }
        Scanner(deque<string> rawLines)
        {
            this->tokens = new deque<Token>();
            tokenize(rawLines);
        }
        ~Scanner()
        {
            delete (this->tokens);
        }

        deque<Token> *getTokens()
        {
            return this->tokens;
        }
        void printTokens()
        {
            for (size_t i = 0; i < this->tokens->size(); i++)
            {
                cout << this->tokens->at(i).text << " is a " << this->tokens->at(i).tType << endl;
            }
        }

    private:
        deque<Token> *tokens;
        bool isNumber(string);
        bool isVariable(string);
        bool isComparitor(string);
        bool isIf(string);
        bool isComment(string);
        bool isWhile(string);
        bool isFor(string);
        bool isBool(string);
        bool isFrom(string);
        bool isTo(string);
        bool isOperator(string);
        bool isEqual(string);
        bool isReserved(string);
        bool isLParen(string text);
        bool isRParen(string text);
        deque<string> toRawLines(ifstream &ifile);
        void tokenize(deque<string> rawLines);
    };
}

#endif