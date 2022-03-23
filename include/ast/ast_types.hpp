#ifndef ast_types_hpp
#define ast_types_hpp

#include <string>
#include <iostream>
#include "ast_expression.hpp"

enum type
{
	VOID,
	INT,
	FLOAT,
	STRING,
	CHAR,
	DOUBLE,
	UNSIGNED_INT,
	NONE
};

class type_declaration
{
    private:
        type variable_type;
    
    public:
        type_declaration(type _variable_type) : variable_type(_variable_type) {}
        type type_of_variable()
        {
            return variable_type;
        }
};

class Types
{
    private:
        type type_of_variable;


    public:
        Types(type _type_of_variable) : type_of_variable(_type_of_variable){}
};
#endif





