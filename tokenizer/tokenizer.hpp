#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>
using namespace std;
const string in_File_1 = "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/basiKexamples/input/basiK2.txt";
const int tokenTypeNumber = 7;
const string tokenTypes [tokenTypeNumber] = {
    "comparitor",
    "variable",
    "number",
    "for",
    "while",
    "if",
    "comment"
};

