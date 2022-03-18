#ifndef ast_types_hpp
#define ast_types_hpp

#include <string>
#include <iostream>
#include "ast_expression.hpp"

enum type
{
    INT
};

class Types;
{
    private:
        type type_of_variable;


    public:
        types(type _type_of_variable) : type_of_variable(_type_of_variable){}
}






