#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include "tokenizer.hpp"
using namespace std;

/*
Class used to generate abstract syntax tree in parsing
*/
class ASTNode
{
public:
    string production;
    string tokenType;
    vector<ASTNode *> children;
    ASTNode();

    void insert(ASTNode *n)
    {
        this->children.push_back(n);
    }
};
#endif