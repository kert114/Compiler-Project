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
            std::string variable_id;
            type_declaration variable_type;
            int variable_address;
    
    public: 
            identifier_declaration (std::string _name_of_variable, std::string _variable_id, type_declaration _variable_type, int _variable_address) 
            : name_of_variable (_name_of_variable), variable_id(_variable_id), variable_type(_variable_type), variable_address(_variable_address) {}
            
            void translate(Context &context, std::string dest_reg){
                context.new_variable(variable_id, variable_type, variable_address);
            }

};

#endif
