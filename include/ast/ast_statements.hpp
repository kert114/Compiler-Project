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
        std::cout << "addiu $sp, $sp, -8" << std::endl;
        if (expression != NULL)
            expression->translate(context);
        std::cout << "sw $v0, 8($fp)" << std::endl;
        context.label_variables[id] = 8;
        std::cout << "addiu $sp, $sp,  8" << std::endl;
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
            context.deallocate_stack();
        }
    }
};
class while_statement : public Statement
{
private:
    ExpressionPtr expression;
    Statement *compound_stmnt;

public:
    while_statement(ExpressionPtr _expression, Statement *_compound_stmnt)
        : expression(_expression), compound_stmnt(_compound_stmnt){}

    void translate(Context &context)
    {
        std::cout<<"$lab1"<<std::endl;
        if (expression != NULL)
        {
            expression->translate(context);
        }
        std::cout<<"li $t3, 0x1"<<std::endl;
        std::cout<<"bne $v0, $t3, $lab2"<<std::endl;
        if (compound_stmnt != NULL){
            compound_stmnt->translate(context);
        }
        std::cout<<"b $lab1"<<std::endl;
        std::cout<<"$lab2:"<<std::endl;
    }
};

#endif
