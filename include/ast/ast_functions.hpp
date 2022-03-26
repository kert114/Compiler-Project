#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>
#include <string>
#include <iostream>
#include <vector>

class Function
    : public Expression
{
private:
    ExpressionPtr arg;

protected:
    Function(ExpressionPtr _arg)
        : arg(_arg)
    {
    }

public:
    virtual ~Function()
    {
        delete arg;
    }

    virtual const char *getFunction() const = 0;

    ExpressionPtr getArg() const
    {
        return arg;
    }

    virtual void print(std::ostream &dst) const override
    {
        dst << getFunction() << "( ";
        arg->print(dst);
        dst << " )";
    }

    virtual int translate(
        Context& context)
    {
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class base_declaration : public Node {};
class Statement : public Node {};

class Declarator
    :public base_declaration
{
    public : 
        std::string variable_name() { return ""; }
        int variable_size() { return 0; }

        void translate_declaration(Context& context, variable& variable, type_declaration declarator_type, std::string dest_reg, int sp, int offset){}
        void translate_declaration_initialisation(Context& context, variable& variable, type_declaration declarator_type, Expression* expression, std::string dest_reg, int sp, int offset){}
};

class Declaration
    : public base_declaration
{
    private : 
        type_declaration TYPE;
        std::vector<Declarator*>* declarations;
    public :
        Declaration(type_declaration _TYPE, std::vector<Declarator*>* _declarations = NULL) 
		: TYPE(_TYPE), declarations(_declarations){}
        
		type get_type() { return TYPE.type_of_variable(); }
};

class function_declaration
    : public base_declaration
{
    private:
        type_declaration* TYPE;
        std::string function_id;
        std::vector<Declaration*>* parameter_list;
        std::vector<Statement*>* statements;

    public:
    function_declaration(type_declaration* _TYPE, std::string _function_id,std::vector<Declaration*>* _parameter_list, std::vector<Statement*>* _statements)
        : TYPE(_TYPE), function_id(_function_id),parameter_list(_parameter_list), statements(_statements){}
    function_declaration(type_declaration* _TYPE, std::string _function_id, std::vector<Statement*>* _statements)
        : TYPE(_TYPE), function_id(_function_id), statements(_statements){}
    virtual void translate(Context& context, std::string dest_reg){
        // context.fetch_stack_pointer();
        std::cout << "addiu $sp $sp "<<"-8"<< std::endl; // change -8 to stackpointer
        //stack size changes but is multiple of 8, fp is always 4 less - also stackpointer is 8 per mips instruction (ish)
        std::cout << "sw $fp "<<"4"<<"($sp)" << std::endl; // change 4 to -stackpointer-4
        std::cout << "move $fp $sp" << std::endl;
        if (statements != NULL)
			    {
			    	for(auto statement = statements->begin(); statement != statements->end(); statement++)
			    	{
			    		(*statement)->translate(context);
			    	}
			    }        
        std::cout << "move $sp $fp" << std::endl;
        std::cout << "lw $fp "<<"4"<<"($sp)" << std::endl; // change 4 to -stackpointer-4
        std::cout << "addiu $sp $sp "<<"8"<< std::endl; // change 8 to -stackpointer
        std::cout << "jr $31" << std::endl;
    }
};

class Identifier_declaration : public Declarator{
    private:
        std::string variable_id;
    public:
        Identifier_declaration(std::string _variable_id) : 
        variable_id(_variable_id){}
        std::string fetch_variable_id(){
            return variable_id;
        }
        void translate_declaration(Context& context, variable& variable, type_declaration declarator_type, std::string dest_reg, int sp, int offset){
            //type_declaration variable_type = variable.fetch_variable_type();
            int variable_addr = variable.fetch_variable_address();
            std::cout<<"sw $fp "<<variable_addr<<"($sp)"<<std::endl;
        }
        void translate_declaration_initialisation(Context& context, variable& variable, type_declaration declarator_type, Expression* expression, std::string dest_reg, int sp, int offset){
            context.allocate_stack();
            int variable_pointer = context.fetch_stack_pointer();
            int variable_addr = variable.fetch_variable_address();
            expression->translate(context, variable, dest_reg);
            context.deallocate_stack();
            std::cout<<"lw $8 "<<variable_pointer<<std::endl;
            std::cout<<"sw $8 "<<variable_addr<<"(sp)"<<std::endl;
        }
};

#endif
