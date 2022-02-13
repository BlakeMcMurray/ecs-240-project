/*
* File: tokenizer.cpp
* Author: Blake McMurray
* Created on 2/9/22
* Description: This program takes raw text and converts to tokens
*/
#include "tokenizer.hpp"

//input: text, output: true or false
bool isNumber(string text){
    std::regex re("\s\d*\.\d\s");
    return(std::regex_match(text, re));
};

//regex to match variables
//I think a simple way to make sure we don't use keywords, is
//to check keywords before checking if its a variable
bool isVariable(string text){
    std::regex re("^[_a-z]\\w*$");
    return(std::regex_match(text, re));
};

//not implemented
bool isComparitor(string text){
    bool b = false;
    return(b);
};

//not implemented
bool isFor(string text){
    bool b = false;
    return(b);
};

//not implemented
bool isWhile(string text){
    bool b = false;
    return(b);
};

//not implemented
bool isIf(string text){
    bool b = false;
    return(b);
};

//not implemented
bool isComment(string text){
    bool b = false;
    return(b);
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


int main()
{   

    string line;

    //input file that the child types into a code block
    ifstream test(inFile2);

    //vector to contain each raw line of text
    vector<string> rawLines;

    //vector of tokens to be returned or printed to a file
    vector<Token> tokens;

    //generates the lines
    while (getline (test, line)) {
        rawLines.push_back(line);
    }

    vector<string> splitted;
    for (int i = 0; i < rawLines.size(); i++) {

        //splits a string into a vector of strings by space delimiter
        boost::split(splitted, rawLines[i], boost:: is_any_of(" "));
        
        for(int j = 0; j < splitted.size(); j++){
            //TODO
        }

    }

    test.close();
    return(0);
}