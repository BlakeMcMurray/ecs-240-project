#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <deque>
#include <unordered_map>
#include <regex>
using std::string;
using std::unordered_map;
using std::make_pair;
using std::endl;
using std::cout;
using std::deque;
using std::regex;
using std::ifstream;
using std::regex_match;
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
    regex re(R"((-?[1-9]\d*(\.\d+)?)|-0\.\d+|0(\.\d+)?)");
    return(regex_match(text, re));
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

bool isLParen(string text){
    return(text == "(");
};

bool isRParen(string text){
    return(text == ")");
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
        int tPos;
        string text;
};

string line;

deque<Token> scanner(ifstream &test){

    //deque to contain each raw line of text
    deque<string> rawLines;

    //deque of tokens to be returned or printed to a file
    deque<Token> tokens;

    //generates the lines


    while (getline (test, line)) {

        regex re(R"(\S)");
        if(regex_search(line, re)){
            trim(line);
            rawLines.push_back(line);
        }

    }

    deque<string> splitted;
    for (int i = 0; i < rawLines.size(); i++) {
        //It will make it easier if comments can only be done
        //as individual lines
        if(isComment(rawLines[i])){
            Token t;
            t.tType = "comment";
            t.text = rawLines[i];
            t.tPos = tokens.size() + 1;
            tokens.push_back(t);
            continue;
        };
        

        //splits a string into a deque of strings by space delimiter
        boost::split(splitted, rawLines[i], boost:: is_any_of(" "));
        for(int j = 0; j < splitted.size(); j++){
            Token t;
            string text = splitted[j];
            if(isBool(text)){
                //assign token value and add it to the tokens deque
                t.tType = "b";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }
            else if(isComparitor(text)){
                //assign token value and add it to the tokens deque
                t.tType = "comp";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }
            else if(isEqual(text)){
                //assign token value and add it to the tokens deque
                t.tType = "=";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }

            else if(isIf(text)){
                //assign token value and add it to the tokens deque
                t.tType = "if";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }

            else if(isWhile(text)){
                //assign token value and add it to the tokens deque
                t.tType = "while";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }
            else if(isFor(text)){
                //assign token value and add it to the tokens deque
                t.tType = "for";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }

            else if(isOperator(text)){
                //assign token value and add it to the tokens deque
                t.tType = "op";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }

            else if(isNumber(text)){
                t.tType = "n";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }
            else if(isVariable(text)){
                t.tType = "var";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }

            else if(isLParen(text)){
                t.tType = "(";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }

            else if (isRParen(text)){
                t.tType = ")";
                t.text = text;
                t.tPos = tokens.size() + 1;
                tokens.push_back(t);
            }
            
            else{
                /*
                What was typed is not a token, should do further analysis
                to decipher what the student typed in.  Might be cool to use a deep learning 
                model to try to guess what the student is trying to write, and provide
                an example written in BasiK.
                */
                cout << "not a token: error" << endl;
                cout << "The text is: " << text << endl;
                return(tokens);
                

            }
        }
    }
    
    Token eof;
    eof.tType = "EOF";
    eof.tPos = tokens.size() + 1;
    tokens.push_back(eof);

    for(int i = 0; i < tokens.size(); i++){
        cout << tokens[i].text << " is a " << tokens[i].tType << endl;

    }

    test.close();
    return(tokens);
}
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

