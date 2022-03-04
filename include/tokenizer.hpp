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
    private:
        deque<Token> *tokens;

        deque<string> toRawLines(ifstream &);
        bool isWhile(string);
        bool isFor(string);
        bool isIf(string);
        bool isAssignment(string);
        bool isComment(string);
        int countTabs(string);
        void tokenize(deque<string>);
        void insertEOF(int);

    public:
        Scanner(deque<string> rawLines)
        {
            this->tokens = new deque<Token>();
            tokenize(rawLines);
            insertEOF(rawLines.size() + 1);
        }
        Scanner(ifstream &ifile) : Scanner(toRawLines(ifile)) {}
        ~Scanner() = default;

        deque<Token> *getTokens() { return this->tokens; }
        static std::string getTokenStr(Token);
        void printTokens();
    };
}

#endif