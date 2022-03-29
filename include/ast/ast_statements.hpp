#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>
#include <vector>
#include "ast_expression.hpp"

class Declaration
    : public Expression
{
private:
    std::string id;
    ExpressionPtr expression;

public:
    Declaration(std::string _id, ExpressionPtr _expression)
        : id(_id), expression(_expression) {}

    virtual void translate(Context &context)
    {
        // std::cout << "#placeholder for Declaration" << std::endl;
<<<<<<< HEAD
        std::cout << "addiu $sp, $sp, -8" << std::endl;
        if (expression != NULL)
            expression->translate(context);
        std::cout << "sw $v0, 8($fp)" << std::endl;
        context.label_variables[id] = 8;
        std::cout << "addiu $sp, $sp,  8" << std::endl;
=======
        std::cout << "addiu $sp, $sp, -80" << std::endl;
        expression->translate(context);
        // std::cout<<context.get_variable_offset(id)<<std::endl;
        std::cout << "sw $v0, 8($fp)"<< std::endl;
        std::cout << "addiu $sp, $sp,  80" << std::endl;
>>>>>>> 4e3db8006b6c74e9df9bcca8d60edee58729d27e
    }
};

class Statement
    : public Expression
{
public:
    Statement() {}
    ~Statement() {}
    virtual void translate(Context &context){};
};

class compound_statement_declaration
    : public Statement
{
private:
    std::vector<Declaration *> *declarations;
    std::vector<Statement *> *statements;

public:
    compound_statement_declaration(std::vector<Declaration *> *_declarations, std::vector<Statement *> *_statements) : declarations(_declarations), statements(_statements) {}
    ~compound_statement_declaration()
    {
        delete statements;
        delete declarations;
    }
    virtual void translate(Context &context)
    {
        if (declarations != NULL)
        {
            for (auto declaration = declarations->begin(); declaration != declarations->end(); declaration++)
            {
                (*declaration)->translate(context);
            }
        }

        if (statements != NULL)
        {
            for (auto statement = statements->begin(); statement != statements->end(); statement++)
            {
                (*statement)->translate(context);
            }
        }
    }
};

class return_statement_declaration : public Statement
{
private:
    Expression *expression;

public:
    return_statement_declaration(Expression *_expression) : expression(_expression) {}
    ~return_statement_declaration()
    {
        delete expression;
    }

    void translate(Context &context)
    {
        if (expression != NULL)
        {
            context.allocate_stack();
            expression->translate(context);
            // std::cout << "lw $v0, 8($sp)"<<std::endl;
            context.deallocate_stack();
        }
    }
};

#endif
