#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>
#include <string>
#include <iostream>

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

    virtual int translate(
        Context& context)
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};



class IntFunction
    : public Function
{
public:
    IntFunction(ExpressionPtr _arg)
        : Function(_arg)
    {
    
    }
    virtual int translate(
        Context& context, std::string dest_reg, int sp, int offset)
    {
        std::cout << "addiu $sp $sp "<<-sp<< std::endl;//stack size changes but is multiple of 8, fp is always 4 less - also sp is 8 per mips instruction (ish)
        std::cout << "sw $fp "<<offset<<"($sp)" << std::endl;
        std::cout << "move $fp $sp" << std::endl;
        /*
        std::cout << "move $sp $fp" << std::endl;
        std::cout << "lw $fp "<<offset<<"($sp)" << std::endl;
        std::cout << "addiu $sp $sp "<<sp<< std::endl;*/
    }
};

#endif
