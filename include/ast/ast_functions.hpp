#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>

class Function
    : public Expression
{
private:
    ExpressionPtr arg;

protected:
    Function(ExpressionPtr _arg)
        : arg(_arg)
    {
    }

public:
    virtual ~Function()
    {
        delete arg;
    }

    virtual const char *getFunction() const = 0;

    ExpressionPtr getArg() const
    {
        return arg;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << getFunction() << "( ";
        arg->print(dst);
        dst << " )";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class LogFunction
    : public Function
{
public:
    LogFunction(ExpressionPtr _arg)
        : Function(_arg)
    {
    }

    virtual const char *getFunction() const
    {
        return "log";
    }

    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double v = getArg()->evaluate(bindings);
        return log(v);
    }

    // TODO-E : Override evaluate, and implement it
};

/*class ExpFunction
    : public Function
{
public:
    ExpFunction(ExpressionPtr _arg)
        : Function(_arg)
    {
    }

    virtual const char *getFunction() const
    {
        return "exp";
    }
    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double v = getArg()->evaluate(bindings);
        return exp(v);
    }
};*/

/*class SqrtFunction
    : public Function
{
public:
    SqrtFunction(ExpressionPtr _arg)
        : Function(_arg)
    {
    }

    virtual const char *getFunction() const
    {
        return "sqrt";
    }
    virtual double evaluate(
        const std::map<std::string, double> &bindings) const override
    {
        double v = getArg()->evaluate(bindings);
        return sqrt(v);
    }
};*/

class IntFunction
    : public Function
{
public:
    IntFunction(ExpressionPtr _arg)
        : Function(_arg)
    {
    
    }
    virtual int translate(
        const std::map<std::string, double> &bindings, std::string dest_reg, int sp, int offset) const override
    {
        std::cout << "addiu $sp $sp "<<-sp<< std::endl;//stack size changes but is multiple of 8, fp is always 4 less - also sp is 8 per mips instruction (ish)
        std::cout << "sw $fp "<<offset<<"($sp)" << std::endl;
        std::cout << "move $fp $sp" << std::endl;
        double v = getArg()->evaluate(bindings);
        std::cout << "move $sp $fp" << std::endl;
        std::cout << "lw $fp "<<offset<<"($sp)" << std::endl;
        std::cout << "addiu $sp $sp "<<sp<< std::endl;
    }
};

#endif
