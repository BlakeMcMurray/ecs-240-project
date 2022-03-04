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
        virtual void evaluate() = 0;

    public:
        explicit Expression(std::string text)
            : text(text) {}
        ~Expression() = default;

        virtual void reevaluate(std::string) = 0;
        static std::string parse_expression_type(std::string);
    };

    // Arithmetic Expression
    class AExp : public Expression
    {
    private:
        int value;
        static const std::unordered_set<std::string> operators;
        void evaluate();

    public:
        AExp(std::string text)
            : Expression(text) {}
        ~AExp() = default;

        void reevaluate(std::string);
        static std::string parse_arithmetic_exp(std::string);
    };

    // Boolean Expression
    class BExp : public Expression
    {
    private:
        bool value;
        static const std::unordered_set<std::string> logicalComparators;
        static const std::unordered_set<std::string> binaryComparators;
        void evaluate();

    public:
        BExp(std::string text)
            : Expression(text) {}
        ~BExp() = default;

        void reevaluate(std::string);
        static std::string parse_bool_exp(std::string);
    };
}

#endif