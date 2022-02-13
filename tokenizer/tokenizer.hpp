#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <unordered_map>
using namespace std;
const string inFile1 = "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/basiKexamples/input/basiK1.txt";
const string inFile2 =  "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/basiKexamples/input/basiK2.txt";
const int tokenTypeNumber = 7;

//Object used for determining token names
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
};

