#include "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/tokenizer.hpp"
using namespace std;

/*
Class used to generate abstract syntax tree in parsing
*/
class AstNode {
    public:
        string production;
        string tokenType;
        vector<AstNode*> children;
        AstNode();


        void insert(AstNode* n){
            this->children.push_back(n);
        }
};