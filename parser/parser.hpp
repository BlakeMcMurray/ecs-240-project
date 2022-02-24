#include "/Users/blakemcmurray/Workspaces/ecs-240-project/tokenizer/tokenizer.hpp"
#include <ostream>

bool isBoolean(Token t){
    regex re(R"((b(( and | or )b)*)|(not b)|(n (<|>|<=|==|>=|<=) n(( <| >| <=| ==| >=| <=) n)*))");
    return(regex_match(t.tType, re));
}





