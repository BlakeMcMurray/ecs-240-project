#include "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/tokenizer.hpp"
#include "/Users/blakemcmurray/Workspaces/ecs-240-project/parser/astNode.cpp"
#include <ostream>
class Parser{
    public:
        AstNode root;
        Parser();

        //function to generate the abstract syntax tree for interpretation
        void generateAST(deque<Token> tokens){
            AstNode* ast = program(tokens);

            if(ast){
                root.insert(ast);
                cout << "Success.  Parser now contains AST." << endl;
            }
            else{
                cout << "Error somewhere." << endl;
            }
        };

};

bool accept(deque<Token> tokens, string value){
    return(tokens[0].tType == value);
};

string peek(deque<Token> tokens, int index){
    return(tokens[index].tType);

};

AstNode* expression(deque<Token> tokens){

/*

    if(tokens.front().tType == "var" && tokens.at(1).tType == "comparitor"){
        tokens.pop_front();
        tokens.pop_front();
        return(expression(tokens));
    }

    else if (tokens.front().tType == "bool"){
        tokens.pop_front();
        
        return(true);
    }

    else if ()
    {
        
    }
    
*/  
    return;
    
};


//Passing tokens by copy, so we should be able to 
//get back to square 1 if it isn't the right production
AstNode* whileLoop(deque<Token> tokens){
    AstNode* w;
    w->production = "While";

    //if it has the beginning structure of a while loop
    if(tokens.front().tType == "while" && tokens.at(1).text == "("){
        tokens.pop_front();
        tokens.pop_front();
        
        //I may need to return a pair instead of just the node
        //the reason is that I need to know how many tokens to remove
        //from the beginning of the list.
        
        AstNode* n= expression(tokens);
        if(n && tokens.front().text == ")"){
            tokens.pop_front();
            if(tokens.front().text == "do"){
                tokens.pop_front();
                n = command(tokens, p);
            }
            
        }

    }

    //Then the command is not a while loop.
    else{
        return(nullptr);
    }

};

AstNode* forLoop(deque<Token> tokens){
    return(true);
};

AstNode* assignment(deque<Token> tokens){
    return(true);
};

AstNode* ifStatement(deque<Token> tokens){
    return(true);
};

AstNode* print(deque<Token> tokens){

};

AstNode* command(deque<Token> tokens){
    AstNode* command;
    command->production = "Command";
    
    AstNode* n = whileLoop(tokens);
    if(n){
        command->insert(n);
        return(command);
    }

    n = assignment(tokens); 
    if(n){
        return(n);
    }
    
    n = print(tokens);
    if(n){
        return(n);
    }

    return(nullptr);
};

AstNode* endOfFile(deque<Token> tokens){
    return(tokens.size() == 1 && tokens[0].tType == "EOF");
};


AstNode* program(deque<Token> tokens){
    
    AstNode* program;
    program->production = "Program";

    //see if the input is a command first, 
    //then try see if it is an EOF
    AstNode* c = command(tokens);
    if(c){
        program->insert(c);
        return(program);
    }

    c = endOfFile(tokens);
    if(c){
        program->insert(c);
        return(program);
    }

    return(nullptr);
    

    

};

AstNode* isexpression(Token t){
    regex re(R"((b(( and | or )b)*)|(not b)|(n (<|>|<=|==|>=|<=) n(( <| >| <=| ==| >=| <=) n)*))");
    return(regex_match(t.tType, re));
};





