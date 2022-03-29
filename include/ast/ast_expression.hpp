#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "ast_context.hpp"

#include <string>
#include <iostream>
#include <map>

#include <memory>

class Expression;

typedef Expression *ExpressionPtr;

class Expression
{
public:
    virtual ~Expression()
    {
    }
    //! Tell an expression to print itself to the given stream
    // virtual void print(std::ostream &dst) const = 0;

    virtual void translate(Context &context) = 0;
};

#endif
