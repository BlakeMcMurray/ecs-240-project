#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <unordered_set>
#include <string>

namespace BasiK
{
    class Expression
    {
    protected:
        std::string text;

    public:
        explicit Expression(std::string text)
            : text(text) {}
        ~Expression() = default;

        virtual void evaluate() = 0;
        static std::string get_expression_type(std::string text);
    };

    class AExp : public Expression
    {
    private:
        int value;
        static const std::unordered_set<std::string> operators;

    public:
        explicit AExp(std::string text)
            : Expression(text) {}
        ~AExp() = default;

        void evaluate();
    };
    const std::unordered_set<std::string> AExp::operators = {"+", "-", "*", "/"};

    class BExp : public Expression
    {
    private:
        bool value;
        static const std::unordered_set<std::string> logicalComparators;
        static const std::unordered_set<std::string> binaryComparators;

    public:
        explicit BExp(std::string text)
            : Expression(text) {}
        ~BExp() = default;

        void evaluate();
    };
    const std::unordered_set<std::string> BExp::logicalComparators = {"and", "or", "not"};
    const std::unordered_set<std::string> BExp::binaryComparators = {"==", "!=", "<", "<=", ">", ">="};
}

#endif