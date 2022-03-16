#include "scanner.hpp"
#include "program.hpp"
#include <map>
#include <sstream>

const string inFile1 = "/Users/noahtarr/School_Offline/ECS240/ecs-240-project/basiKexamples/input/shouldPass/basiK1.txt";
const string inFile2 = "/Users/noahtarr/School_Offline/ECS240/ecs-240-project copy/basiKexamples/input/shouldPass/basiK2.txt";

int main()
{
    ifstream inFile(inFile2);
    BasiK::Scanner scnr(inFile);
    deque<BasiK::Line> lines = *scnr.get_lines();
    scnr.print_lines();
    BasiK::Program prgm(lines);

    return 0;
}