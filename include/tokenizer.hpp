#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <unordered_map>
#include <regex>
#include "token.hpp"
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

        void printToken(Token);
        void printTokens();

    private:
        deque<Token> *tokens;

        deque<string> toRawLines(ifstream &);
        bool isWhile(string);
        bool verifyWhile(string);
        bool isFor(string);
        bool verifyFor(string);
        bool isIf(string);
        bool verifyIf(string);
        bool isAssignment(string);
        bool verifyAssignment(string);
        bool isComment(string);
        void insertEOF(int);
        int countTabs(string);
        void tokenize(deque<string>);
    };
}

#endif