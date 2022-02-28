#include "tokenizer.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

const string inFile1 = "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/basiKexamples/input/shouldPass/basiK1.txt";
const string inFile2 = "/Users/noahtarr/School Offline/ECS240/ecs-240-project/tokenizer/basiKexamples/input/shouldPass/basiK2.txt";

int main()
{
    ifstream inFile(inFile2);
    BasiK::Scanner scnr(inFile);
    deque<BasiK::Token> *tokens = scnr.getTokens();
    scnr.printTokens();
    return (0);
}