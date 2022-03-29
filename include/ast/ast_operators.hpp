#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include "ast_expression.hpp"

class unary_expression
    : public Expression
{
private:
    ExpressionPtr left;
    std::string op;

public:
    unary_expression(ExpressionPtr _left, std::string _operator)
        : left(_left), op(_operator)
    {
    }

    virtual void translate(Context &context)
    {
        /*double left = getLeft()->translate(context, "$3");
        double right = getRight()->translate (context, "$4");
        std::cout << "addiu" << dest_reg << " $3 $4" << std::endl;*/
    }
};

class binary_expression
    : public Expression
{
private:
    ExpressionPtr left;
    std::string op; // operator of the binary expression
    ExpressionPtr right;
    bool isAssign;

public:
    binary_expression(ExpressionPtr _left, std::string _operator, ExpressionPtr _right)
        : left(_left), op(_operator), right(_right), isAssign(false)
    {
    }

    binary_expression(ExpressionPtr _left, std::string _operator, ExpressionPtr _right, bool _isAssign)
        : left(_left), op(_operator), right(_right), isAssign(_isAssign)
    {
    }

    virtual void translate(Context &context)
    {
        if (op == "+")
        {
            left->translate(context);
            std::cout << "move $t0, $v0" << std::endl;
            right->translate(context);
            std::cout << "move $t1, $v0" << std::endl;
            std::cout << "add $v0, $t0, $t1" << std::endl;
        }
        if (op == "-")
        {
            left->translate(context);
            std::cout << "move $t0, $v0" << std::endl;
            right->translate(context);
            std::cout << "move $t1, $v0" << std::endl;
            std::cout << "sub $v0, $t0, $t1" << std::endl;
        }
        if (op == "*")
        {
            left->translate(context);
            std::cout << "move $t0, $v0" << std::endl;
            right->translate(context);
            std::cout << "move $t1, $v0" << std::endl;
            std::cout << "mul $v0, $t0, $t1" << std::endl;
        }
        if (op == "&")
        {
            left->translate(context);
            std::cout << "move $t0, $v0" << std::endl;
            right->translate(context);
            std::cout << "move $t1, $v0" << std::endl;
            std::cout << "and $v0, $t0, $t1" << std::endl;
        }
        if (op == "|")
        {
            left->translate(context);
            std::cout << "move $t0, $v0" << std::endl;
            right->translate(context);
            std::cout << "move $t1, $v0" << std::endl;
            std::cout << "or $v0, $t0, $t1" << std::endl;
        }
        if (op == "==")
        {
            left->translate(context);
            std::cout << "move $t0, $v0" << std::endl;
            right->translate(context);
            std::cout << "move $t1, $v0" << std::endl;
            // std::cout << "xor $v0, $t0, $t1" << std::endl;
            // std::cout << "sltu $v0 $v0 1" << std::end;
            // std::cout << "andi $v0 $v0 0x00ff" << std::endl;
        }
        if (op == "<")
        {
            left->translate(context);
            std::cout << "move $t0, $v0" << std::endl;
            right->translate(context);
            std::cout << "move $t1, $v0" << std::endl;
            std::cout << "slt $v0, $t0, $t1" << std::endl;
        }
        /*double left = getLeft()->translate(context, "$3");
        double right = getRight()->translate (context, "$4");
        std::cout << "addiu" << dest_reg << " $3 $4" << std::endl;*/
    }
};

class ternary_expression
    : public Expression
{
private:
    ExpressionPtr condition;
    ExpressionPtr true_branch;
    ExpressionPtr false_branch;

public:
    ternary_expression(ExpressionPtr _condition, ExpressionPtr _tb, ExpressionPtr _fb)
        : condition(_condition), true_branch(_tb), false_branch(_fb)
    {
    }

    virtual void translate(Context &context)
    {
        /*double left = getLeft()->translate(context, "$3");
        double right = getRight()->translate (context, "$4");
        std::cout << "addiu" << dest_reg << " $3 $4" << std::endl;*/
    }
};

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;

protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left), right(_right)
    {
    }

public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const = 0;

    ExpressionPtr getLeft() const
    {
        return left;
    }

    ExpressionPtr getRight() const
    {
        return right;
    }

    /*virtual void print(std::ostream &dst) const override
    {
        dst << "( ";
        left->print(dst);
        dst << " ";
        dst << getOpcode();
        dst << " ";
        right->print(dst);
        dst << " )";
    }*/
};

class AddOperator : public Operator
{
    /*protected:
            virtual const char *getOpcode() const override
            {return "+";}*/
public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right) {}
    virtual void translate(Context &context)
    {
        /*double left = getLeft()->translate(context, "$3");
        double right = getRight()->translate (context, "$4");
        std::cout << "addiu" << dest_reg << " $3 $4" << std::endl;*/
    }
};

class SubOperator : public Operator
{
public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right) {}
    virtual void translate(Context &context)
    {
        /*double left = getLeft()->translate(context, "$3");
        double right = getRight()->translate (context, "$4");
        std::cout << "subiu" << dest_reg << " $3 $4" << std::endl;*/
    }
};

class MulOperator : public Operator
{
public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right) {}
    virtual void translate(Context &context)
    {
        /*double left = getLeft()->translate(context, "$3");
        double right = getRight()->translate (context, "$4");
        std::cout << "multu" << dest_reg << " $3 $4" << std::endl;*/
    }
};

class DivOperator : public Operator
{
public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right) {}
    virtual void translate(Context &context)
    {
        /*double left = getLeft()->translate(context, "$3");
        double right = getRight()->translate (context, "$4");
        std::cout << "divu" << dest_reg << " $3 $4" << std::endl;*/
    }
};

class LogicalAndOperator : public Operator
{
public:
    LogicalAndOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right) {}
};

class LogicalOrOperator : public Operator
{
public:
    LogicalOrOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right) {}
};

class LogicalRightShiftOperator : public Operator
{
public:
    LogicalRightShiftOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right) {}
};

class LogicalLeftShiftOperator : public Operator
{
public:
    LogicalLeftShiftOperator(ExpressionPtr _left, ExpressionPtr _right) : Operator(_left, _right) {}
};

#endif
