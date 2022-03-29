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
    Variable(std::string _id)
        : id(_id)
    {
    }

    virtual void translate(Context &context)
    {
        // need to get variable's offset from context
        int var_offset = context.get_variable_offset(id);
        std::cout << "lw "
                  << "$2," << var_offset << "($fp)" << std::endl;
    }
};

class Integer
    : public Expression
{
private:
    double value;

public:
    Integer(double _value)
        : value(_value)
    {
    }

    double getValue()
    {
        return value;
    }

    virtual void translate(
        Context &context)
    {

        int stack_pointer = context.fetch_stack_pointer();
        std::string destination_register = "$2";

        std::cout << "li "
                  << "$2, " << value << std::endl;

        context.store_register(destination_register, stack_pointer);
    }
};
/*
class identifier_declaration : public Expression
{
    private:
            std::string name_of_variable;
            std::string variable_id;
            type_declaration variable_type;
            int variable_address;

    public:
            identifier_declaration (std::string _name_of_variable, std::string _variable_id, type_declaration _variable_type, int _variable_address)
            : name_of_variable (_name_of_variable), variable_id(_variable_id), variable_type(_variable_type), variable_address(_variable_address) {}

            void translate(Context &context){
                context.new_variable(variable_id, variable_type, variable_address);
            }

};
*/
#endif
