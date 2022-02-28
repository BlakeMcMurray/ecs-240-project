/*
* File: tokenizer.cpp
* Author: Blake McMurray
* Created on 2/9/22
* Description: This program takes raw text and converts to tokens
*/
#include "tokenizer.hpp"

int main()
{   
    ifstream inFile(inFile2);
    deque<Token> tokens = scanner(inFile);
    return(0);
}