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

//std::regex to match variables
//I think a simple way to make sure we don't use keywords, is
//to check keywords before checking if its a variable'
//Ideally the std::regex would perfectly map allowed variables to the output
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

        //any lines that are just white space are not included

        rawLines.push_back(line);
        cout << line << endl;

    }

    vector<string> splitted;
    for (int i = 0; i < rawLines.size(); i++) {
        //It will make it easier if comments can only be done
        //as individual lines
        if(isComment(rawLines[i])){
            Token t;
            t.tType = "comment";
            t.text = rawLines[i];
            continue;
        };

        std::regex re("\S");
        if(!std::regex_search(rawLines[i], re)){
            continue;
        }

        //splits a string into a vector of strings by space delimiter
        boost::split(splitted, rawLines[i], boost:: is_any_of(" "));
        
        for(int j = 0; j < splitted.size(); j++){
            Token t;
            string text = splitted[j];
            if(isBool(text)){
                //assign token value and add it to the tokens vector
                t.tType = "bool";
                t.text = text;
                tokens.push_back(t);
            }
            else if(isComparitor(text)){
                //assign token value and add it to the tokens vector
                t.tType = "comparitor";
                t.text = text;
                tokens.push_back(t);
            }
            else if(isEqual(text)){
                //assign token value and add it to the tokens vector
                t.tType = "equal";
                t.text = text;
                tokens.push_back(t);
            }

            else if(isIf(text)){
                //assign token value and add it to the tokens vector
                t.tType = "if";
                t.text = text;
                tokens.push_back(t);
            }

            else if(isOperator(text)){
                //assign token value and add it to the tokens vector
                t.tType = "operator";
                t.text = text;
                tokens.push_back(t);
            }
            else if(isWhile(text)){
                //assign token value and add it to the tokens vector
                t.tType = "while";
                t.text = text;
                tokens.push_back(t);
            }
            else if(isFor(text)){
                //assign token value and add it to the tokens vector
                t.tType = "for";
                t.text = text;
                tokens.push_back(t);
            }

            else if(isOperator(text)){
                //assign token value and add it to the tokens vector
                t.tType = "operator";
                t.text = text;
                tokens.push_back(t);
            }

            else if(isNumber(text)){
                t.tType = "number";
                t.text = text;
                tokens.push_back(t);
            }
            else if(isVariable(text)){
                t.tType = "var";
                t.text = text;
                tokens.push_back(t);
            }
            
            else{
                /*
                What was typed is not a token, should do further analysis
                to decipher what the student typed in.  Might be cool to use a deep learning 
                model to try to guess what the student is trying to write, and provide
                an example written in BasiK.
                */
                cout << "not a token: error";
                return(-1);
                

            }
        }
    }

    cout << "in" << endl;
    for(int i = 0; i < tokens.size(); i++){
        cout << tokens[i].text << " is a " << tokens[i].tType << endl;

    }

    test.close();
    return(0);
}