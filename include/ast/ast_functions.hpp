#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>
#include <string>
#include <iostream>
#include <vector>

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
        Context &context)
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class base_declaration : public Node
{
};
class Statement : public Node
{
};

class Declarator
    : public base_declaration
{
public:
    std::string variable_name() { return ""; }
    int variable_size() { return 0; }

    void compile_declaration(Context &context, type_declaration declarator_type) {}
    void compile_declaration_initialisation(Context &context, type_declaration declarator_type, Expression *expression) {}
};

class Declaration
    : public base_declaration
{
private:
    type_declaration TYPE;
    std::vector<Declarator *> *declarations;

public:
    Declaration(type_declaration _TYPE, std::vector<Declarator *> *_declarations = NULL)
        : TYPE(_TYPE), declarations(_declarations) {}

    type get_type() { return TYPE.type_of_variable(); }
};

class function_declaration
    : public base_declaration
{
private:
    type_declaration *TYPE;
    std::string function_id;
    std::vector<Declaration *> *parameter_list;
    std::vector<Statement *> *statements;

public:
    function_declaration(type_declaration *_TYPE, std::string _function_id, std::vector<Declaration *> *_parameter_list, std::vector<Statement *> *_statements)
        : TYPE(_TYPE), function_id(_function_id), parameter_list(_parameter_list), statements(_statements)
    {
    }
    virtual int translate(
        Context &context, std::string dest_reg, int sp, int offset)
    {
        std::cout << "addiu $sp $sp " << -sp << std::endl;
        // stack size changes but is multiple of 8, fp is always 4 less - also sp is 8 per mips instruction (ish)
        std::cout << "sw $fp " << offset << "($sp)" << std::endl;
        std::cout << "move $fp $sp" << std::endl;
        if (statements != NULL)
        {
            for (auto statement = statements->begin(); statement != statements->end(); statement++)
            {
                (*statement)->translate(context);
            }
        }
        std::cout << "move $sp $fp" << std::endl;
        std::cout << "lw $fp " << offset << "($sp)" << std::endl;
        std::cout << "addiu $sp $sp " << sp << std::endl;
        std::cout << "jr $31" << std::endl;
    }
};

#endif
