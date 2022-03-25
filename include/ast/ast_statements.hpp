#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>
#include <vector>
#include "ast_expression.hpp"
#include "ast_functions.hpp"

class basic_statement : public Statement
{
private:
    Expression *expression;

public:
    basic_statement(Expression *_expression) : expression(_expression) {}
    virtual void translate(Context &context, std::string dest, int sp, int offset)
    {
        if (expression != NULL)
        {
            context.allocate_stack();
            expression->translate(context, dest, sp, offset);
            context.deallocate_stack();
        }
    }
};

class compound_statement_declaration
    : public Statement
{
private:
    std::vector<Statement *> *statements;
    std::vector<Declaration *> *declarations;

public:
    compound_statement_declaration(std::vector<Statement *> *_statements = NULL, std::vector<Declaration *> *_declarations = NULL) : statements(_statements), declarations(_declarations) {}

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

class return_statement : public Statement
{
private:
    Expression *expression;

public:
    return_statement(Expression *_expression) : expression(_expression) {}

    void translate(Context &context, std::string dest, int sp, int offset)
    {
        if (expression != NULL)
        {
            context.allocate_stack();
            expression->translate(context, dest, sp, offset);
            context.deallocate_stack();
        }
    }
};

#endif
