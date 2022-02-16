/*
* File: tokenizer.cpp
* Author: Blake McMurray
* Created on 2/9/22
* Description: This program takes raw text and converts to tokens
*/
#include "tokenizer.hpp"

//input: text, output: true or false
bool isNumber(string text){
    std::regex re("(-?[1-9]\d*(\.\d+)?)|-0\.\d+|0(\.\d+)?");
    return(std::regex_match(text, re));
};

//regex to match variables
//I think a simple way to make sure we don't use keywords, is
//to check keywords before checking if its a variable'
//Ideally the regex would perfectly map allowed variables to the output
//true and any thing that is not an allowed variable would be mapped to false
bool isVariable(string text){
    std::regex re("([a-z]|[A-Z]|_)+(\d|[a-z]|[A-Z]|_)*");
    return(std::regex_match(text, re));
};

bool isComparitor(string text){
    bool b = (text == "==") || (text == "!=") || (text == "<") || (text == ">") || (text == "<=") || (text == ">=");
    return(b);
};

//not implemented
bool isIf(string text){
    bool b = false;
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

        //It will make it easier if comments can only be done
        //as individual lines
        if(isComment(rawLines[i])){
            Token t;
            t.tType = "Comment";
            t.text = rawLines[i];
            continue;
        };

        //splits a string into a vector of strings by space delimiter
        boost::split(splitted, rawLines[i], boost:: is_any_of(" "));
        
        for(int j = 0; j < splitted.size(); j++){
            Token t;
            string text = splitted[j];
            if(isNumber(text)){
                //assign token value and add it to the tokens vector
                t.tType = "number";
                t.text = rawLines[i];
            }
            else if(isVariable(text)){
                //assign token value and add it to the tokens vector
                t.tType = "var";
                t.text = rawLines[i];
            }

            else if(isBool(text)){
                //assign token value and add it to the tokens vector
                t.tType = "var";
                t.text = rawLines[i];
            }


            else if(isComparitor(text)){
                //assign token value and add it to the tokens vector
                t.tType = "comparitor";
                t.text = rawLines[i];
            }
            else if(isIf(text)){
                //assign token value and add it to the tokens vector
                t.tType = "if";
                t.text = rawLines[i];
            }
            else if(isWhile(text)){
                //assign token value and add it to the tokens vector
                t.tType = "while";
                t.text = rawLines[i];
            }
            else if(isFor(text)){
                //assign token value and add it to the tokens vector
                t.tType = "for";
                t.text = rawLines[i];
            }
            else{
                /*
                What was typed is not a token, should do further analysis
                to decipher what the student typed in.  Might be cool to use a deep learning 
                model to try to guess what the student is trying to write, and provide
                an example written in BasiK.
                */
                cout << "not a token: error";
                

            }
        }
    }

    test.close();
    return(0);
}