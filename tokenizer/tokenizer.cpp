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

bool isComparitor(string text){
    bool b = false;
    return(b);
};

bool isFor(string text){
    bool b = false;
    return(b);
};

bool isWhile(string text){
    bool b = false;
    return(b);
};

bool isIf(string text){
    bool b = false;
    return(b);
};

bool isComment(string text){
    bool b = false;
    return(b);
};

class Tokenizer {      
    public:            
        int myNum;        
        string myString;  
};

class Token {
    public:
        string tType;
        int sPos;
        string text;
        



};


int main()
{   

    string line;
    ifstream test(inFile2);
    vector<string> rawLines;
    vector<Token> tokens;

    while (getline (test, line)) {
        rawLines.push_back(line);
    }



    vector<string> splitted;
    for (int i = 0; i < rawLines.size(); i++) {
        boost::split(splitted, rawLines[i], boost:: is_any_of(" "));
        
        for(int j = 0; j < splitted.size(); j++){
            TokenNames tNames;

        }

    }





    
    // Close the file
    test.close();
    return(0);
}