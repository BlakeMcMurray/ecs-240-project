#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>
using namespace std;

const string inFile1 = "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/basiKexamples/input/shouldPass/basiK1.txt";
const string inFile2 =  "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/basiKexamples/input/shouldPass/basiK2.txt";

//reserved words to check while tokenizing
class ReservedWords {     
  public:           
    ReservedWords() {     
        unordered_map<string, bool> rWords;
        rWords.insert(make_pair("for", false));
        rWords.insert(make_pair("if",false));
        rWords.insert(make_pair("from", false));
        rWords.insert(make_pair("while", false));
        rWords.insert(make_pair("do", false));
        rWords.insert(make_pair("int", false));
    };
};



//Object used for determining token names
//we probably don't actuall need this, but just in case
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

