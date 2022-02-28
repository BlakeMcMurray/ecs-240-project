#include "parser.hpp"
#include "../tokenizer/tokenizer.hpp"
int main(){

    ifstream inFile(inFile2);
    deque<Token> tokens = scanner(inFile);   
    Parser parser;
    parser.generateAST(tokens);

    //Then we need to interpret the generated tree
    //parser.interpret(); 
    return(1);

}