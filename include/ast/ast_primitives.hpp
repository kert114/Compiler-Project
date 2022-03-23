#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>
#include "ast_expression.hpp"
#include "ast_context.hpp"

class Variable
    : public Expression
{
private:
    std::string id;

public:
    Variable(const std::string &_id)
        : id(_id)
    {
    }

    const std::string getId() const
    {
        return id;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << id;
    }

    virtual double translate(
        Context& context)
    {
    }
};

class Integer
    : public Expression
{
private:
    int value;

public:
    Integer(double _value)
        : value(_value)
    {
    }

    double getValue() const
    {
        return value;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << value;
    }

    virtual double translate(
        Context& context, std::string dest)
    {
        
        int stack_pointer = context.get_stack_pointer();
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
