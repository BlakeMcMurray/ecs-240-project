#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <unordered_map>
#include <regex>
#include "line.hpp"
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
        deque<Line> *lines;

        deque<string> toRawLines(ifstream &);
        bool isWhile(string);
        bool isFor(string);
        bool isIf(string);
        bool isAssignment(string);
        bool isPrint(string);
        bool isComment(string);
        int countTabs(string);
        void scan(deque<string>);
        void insertEOF(int);

    public:
        Scanner(deque<string> rawLines)
        {
            this->lines = new deque<Line>();
            scan(rawLines);
            insertEOF(rawLines.size() + 1);
        }
        Scanner(ifstream &ifile) : Scanner(toRawLines(ifile)) {}
        ~Scanner() = default;

        deque<Line> *get_lines() { return this->lines; }
        static std::string get_formatted_line(Line);
        void print_lines();
        static std::string remove_spaces(std::string);
    };
}

#endif