// #ifndef PARSER_HPP
// #define PARSER_HPP

// #include <iostream>
// #include <string>
// #include <deque>
// #include "tokenizer.hpp"
// #include "astNode.hpp"
// using std::cout;
// using std::deque;
// using std::endl;
// using std::string;
// using namespace BasiK;

// namespace BasiK
// {
//     class Parser
//     {
//     public:
//         ASTNode root;
//         Parser(deque<Token> tokens)
//         {
//             generateAST(tokens);
//         }

//     private:
//         void generateAST(deque<Token> tokens);
//     };

//     bool accept(deque<Token> tokens, string value)
//     {
//         return (tokens[0].tType == value);
//     }

//     string peek(deque<Token> tokens, int index)
//     {
//         return (tokens[index].tType);
//     }

//     ASTNode *expression(deque<Token> tokens)
//     {
//         /*

//             if(tokens.front().tType == "var" && tokens.at(1).tType == "comparitor"){
//                 tokens.pop_front();
//                 tokens.pop_front();
//                 return(expression(tokens));
//             }

//             else if (tokens.front().tType == "bool"){
//                 tokens.pop_front();

//                 return(true);
//             }

//             else if ()
//             {

//             }

//         */
//         return (nullptr);
//     }

//     // Passing tokens by copy, so we should be able to
//     // get back to square 1 if it isn't the right production
//     ASTNode *whileLoop(deque<Token> tokens)
//     {
//         ASTNode *w;
//         w->production = "While";

//         // if it has the beginning structure of a while loop
//         if (tokens.front().tType == "while" && tokens.at(1).text == "(")
//         {
//             tokens.pop_front();
//             tokens.pop_front();

//             // I may need to return a pair instead of just the node
//             // the reason is that I need to know how many tokens to remove
//             // from the beginning of the list.

//             ASTNode *n = expression(tokens);
//             if (n && tokens.front().text == ")")
//             {
//                 tokens.pop_front();
//                 if (tokens.front().text == "do")
//                 {
//                     tokens.pop_front();
//                     // n = command(tokens);
//                 }
//             }
//         }

//         // Then the command is not a while loop.
//         return (nullptr);
//     }

//     ASTNode *forLoop(deque<Token> tokens)
//     {
//         return (nullptr);
//     }

//     ASTNode *assignment(deque<Token> tokens)
//     {
//         return (nullptr);
//     }

//     ASTNode *ifStatement(deque<Token> tokens)
//     {
//         return (nullptr);
//     }

//     ASTNode *print(deque<Token> tokens)
//     {
//         return (nullptr);
//     }

//     ASTNode *command(deque<Token> tokens)
//     {
//         ASTNode *command;
//         command->production = "Command";

//         ASTNode *n = whileLoop(tokens);
//         if (n)
//         {
//             command->insert(n);
//             return (command);
//         }

//         n = assignment(tokens);
//         if (n)
//         {
//             return (n);
//         }

//         n = print(tokens);
//         if (n)
//         {
//             return (n);
//         }

//         return (nullptr);
//     }

//     ASTNode *endOfFile(deque<Token> tokens)
//     {
//         // return (tokens.size() == 1 && tokens[0].tType == "EOF");
//         return (nullptr);
//     }

//     ASTNode *program(deque<Token> tokens)
//     {

//         ASTNode *program;
//         program->production = "Program";

//         // see if the input is a command first,
//         // then try see if it is an EOF
//         ASTNode *c = command(tokens);
//         if (c)
//         {
//             program->insert(c);
//             return (program);
//         }

//         c = endOfFile(tokens);
//         if (c)
//         {
//             program->insert(c);
//             return (program);
//         }

//         return (nullptr);
//     }

//     ASTNode *isexpression(Token t)
//     {
//         regex re(R"((b(( and | or )b)*)|(not b)|(n (<|>|<=|==|>=|<=) n(( <| >| <=| ==| >=| <=) n)*))");
//         // return (regex_match(t.tType, re));

//         return (nullptr);
//     }
// }
// #endif