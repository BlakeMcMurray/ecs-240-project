/*
* File: tokenizer.cpp
* Author: Blake McMurray
* Created on 2/9/22
* Description: This program takes raw text and converts to tokens
*/

#include "tokenizer.hpp"
using namespace std;

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
            

            
        }

    }





    
    // Close the file
    test.close();
    return(0);
}