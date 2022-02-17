/*
* File: tokenizer.cpp
* Author: Blake McMurray
* Created on 2/9/22
* Description: This program takes raw text and converts to tokens
*/
#include "tokenizer.hpp"

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

        regex re(R"(\S)");
        if(regex_search(line, re)){
            trim(line);
            rawLines.push_back(line);
        }

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
                cout << "not a token: error" << endl;
                cout << "The text is: " << text << endl;
                return(-1);
                

            }
            
        }
    }

    for(int i = 0; i < tokens.size(); i++){
        cout << tokens[i].text << " is a " << tokens[i].tType << endl;

    }

    test.close();
    return(0);
}