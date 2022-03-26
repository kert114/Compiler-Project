#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>
#include "ast_expression.hpp"
#include "ast_context.hpp"

class Variable : public Expression{};

class Integer
    : public Variable
{
private:
    int value;

public:
    Integer(double _value)
        : value(_value)
    {
    }

    double getValue()
    {
        return value;
    }

    virtual void print(std::ostream &dst) 
    {
        dst << value;
    }

    virtual void translate(
        Context& context, variable& variable, std::string dest)
    {
        
        int stack_pointer = context.fetch_stack_pointer();
        std::string destination_register = "$2";

        std::cout << "li " << dest << value << std::endl;
        
        context.store_register(destination_register, stack_pointer);
    }
};

class identifier_declaration : public Variable
{
    private:
            std::string name_of_variable;
    
    public: 
            identifier_declaration ( std::string _name_of_variable) : name_of_variable (_name_of_variable) {}

};

#endif
