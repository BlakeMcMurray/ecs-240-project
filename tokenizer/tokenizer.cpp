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
    ifstream test(in_File_1);
    vector<string> rawLines;

    while (getline (test, line)) {
        rawLines.push_back(line);
    }

    for (int i = 0; i < rawLines.size(); i++) {
        
    }





    
    // Close the file
    test.close();
    return(0);
}