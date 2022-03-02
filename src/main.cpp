// #include "parser.hpp"
#include "tokenizer.hpp"

const string inFile1 = "/Users/noahtarr/School_Offline/ECS240/ecs-240-project/basiKexamples/input/shouldPass/basiK1.txt";
const string inFile2 = "/Users/noahtarr/School_Offline/ECS240/ecs-240-project/basiKexamples/input/shouldPass/basiK2.txt";

int main()
{
    ifstream inFile(inFile2);
    BasiK::Scanner scnr(inFile);
    deque<BasiK::Token> tokens = *scnr.getTokens();
    scnr.printTokens();

    // BasiK::Parser parser(tokens);

    // Then we need to interpret the generated tree
    // parser.interpret();
    return (1);
}