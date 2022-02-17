#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>
using std::string;
using std::unordered_map;
using std::make_pair;
using std::endl;
using std::cout;
using std::vector;
using std::regex;
using std::ifstream;
using namespace boost::algorithm;




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

//input: text, output: true or false
bool isNumber(string text){
    cout << text << endl;
    std::regex re(R"((-?[1-9]\d*(\.\d+)?)|-0\.\d+|0(\.\d+)?)");
    return(std::regex_match(text, re));
};

//std::regex to match variables
//I think a simple way to make sure we don't use keywords, is
//to check keywords before checking if its a variable'
//Ideally the std::regex would perfectly map allowed variables to the output
//true and any thing that is not an allowed variable would be mapped to false
bool isVariable(string text){
    regex re(R"(([a-z]|[A-Z]|_)+(\d|[a-z]|[A-Z]|_)*)");
    return(regex_match(text, re));
};

bool isComparitor(string text){
    bool b = (text == "==") || (text == "!=") || (text == "<") || (text == ">") || (text == "<=") || (text == ">=");
    return(b);
};

//not implemented
bool isIf(string text){
    bool b = text == "if";
    return(b);
};

//this will apply to individual lines, not 
//space delimited strings
bool isComment(string text){
    return(text[0] == '#');
};

//not implemented
bool isWhile(string text){

    bool b = text == "while";
    return(b);

};

bool isFor(string text){
    bool b = text == "for";
    return(b);
};

bool isBool(string text){
    bool b = (text == "true" || text == "false");
    return(b);
};

bool isFrom(string text){
    bool b = (text == "from");
    return(b);
};

bool isTo(string text){
    bool b = (text == "to");
    return(b);
};

bool isOperator(string text){
    bool b = (text == "+"|text == "-" | text == "/"| text == "*"| text == "**" | text == "log");
    return(b);
};

bool isEqual(string text){
    bool b = text == "=";
    return(b);
};

//function to check if word is reserved
bool isReserved(string text){
    return(isBool(text) | isFor(text) | isWhile(text) | isIf(text) | isFrom(text) | isTo(text));
};

//unsure if we need a tokenizer object, but it is here 
//just in case
class Tokenizer {      
    public:            
        int myNum;        
        string myString;  
};

//token object that holds the type of token,
//the position in the original text and the 
//raw text that the token consists of
class Token {
    public:
        string tType;
        int sPos;
        string text;
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

