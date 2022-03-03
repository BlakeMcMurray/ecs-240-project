#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <unordered_set>
#include <string>

namespace BasiK
{
    // Expression Base Class
    class Expression
    {
    protected:
        std::string text;

    public:
        explicit Expression(std::string text)
            : text(text) {}
        ~Expression() = default;

        virtual void evaluate() = 0;
        virtual void reevaluate(std::string) = 0;
        static std::string parse_expression_type(std::string);
    };

    // Arithmetic Expression
    class AExp : public Expression
    {
    private:
        int value;
        static const std::unordered_set<std::string> operators;

    public:
        AExp(std::string text)
            : Expression(text) {}
        ~AExp() = default;

        void evaluate();
        void reevaluate(std::string);
        static std::string parse_arithmetic_exp(std::string);
    };
    const std::unordered_set<std::string> AExp::operators = {"+", "-", "*", "/"};

    // Arithmetic Expression
    class BExp : public Expression
    {
    private:
        bool value;
        static const std::unordered_set<std::string> logicalComparators;
        static const std::unordered_set<std::string> binaryComparators;

    public:
        BExp(std::string text)
            : Expression(text) {}
        ~BExp() = default;

        void evaluate();
        void reevaluate(std::string);
        static std::string parse_bool_exp(std::string);
    };
    const std::unordered_set<std::string> BExp::logicalComparators = {"and", "or", "not"};
    const std::unordered_set<std::string> BExp::binaryComparators = {"==", "!=", "<", "<=", ">", ">="};
}

#endif