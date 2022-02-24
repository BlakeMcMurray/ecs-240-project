/*
 * File: tokenizer.cpp
 * Author: Blake McMurray
 * Created on 2/9/22
 * Description: This program takes raw text and converts to tokens
 */
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include "boost/algorithm/string.hpp"
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>
using std::cout;
using std::endl;
using std::ifstream;
using std::make_pair;
using std::regex;
using std::string;
using std::unordered_map;
using std::vector;
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
            this->tokens = new vector<Token>();
            scan(toRawLines(ifile));
        }
        Scanner(vector<string> rawLines)
        {
            this->tokens = new vector<Token>();
            scan(rawLines);
        };
        ~Scanner() = default;
        vector<BasiK::Token> *getTokens()
        {
            return this->tokens;
        }

    private:
        vector<Token> *tokens;
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
        vector<string> toRawLines(ifstream &ifile);
        void scan(vector<string>);
    };
}

#endif