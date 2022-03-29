#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"
#include "ast_statements.hpp"

#include <cmath>
#include <string>
#include <iostream>
#include <vector>

class Statement;

class function_declaration
    : public Expression
{
private:
    std::string function_id;
    Statement *compound_stmnt;
    int numArgs;
    std::string var0;
    std::string var1;
    std::string var2;
    std::string var3;

public:
    function_declaration(std::string _function_id, Statement *_compound_stmnt)
        : function_id(_function_id), compound_stmnt(_compound_stmnt), numArgs(0) {}

    function_declaration(std::string _function_id, Statement *_compound_stmnt, std::string _var0, std::string _var1)
        : function_id(_function_id), compound_stmnt(_compound_stmnt), numArgs(2), var0(_var0), var1(_var1) {}

    virtual void translate(Context &context)
    {
        std::cout << ".globl " << function_id << std::endl;
        std::cout << function_id << ":" << std::endl;
        // context.fetch_stack_pointer();
        std::cout << "addiu $sp, $sp, "
                  << "-128" << std::endl; // change -8 to stackpointer
        // stack size changes but is multiple of 8, fp is always 4 less - also stackpointer is 8 per mips instruction (ish)
        std::cout << "sw $fp, "
                  << "4($sp)" << std::endl; // change 4 to -stackpointer-4
        std::cout << "move $fp, $sp" << std::endl;

        if (numArgs == 2)
        {
            context.new_variable(var0, 12);
            context.new_variable(var1, 16);
            std::cout << "sw $a0, 12($fp)" << std::endl;
            std::cout << "sw $a1, 16($fp)" << std::endl;
        }

        if (compound_stmnt != NULL)
        {
            compound_stmnt->translate(context);
        }
        std::cout << "move $sp, $fp" << std::endl;
        std::cout << "lw $fp, "
                  << "4($sp)" << std::endl; // change 4 to -stackpointer-4
        std::cout << "addiu $sp, $sp, "
                  << "128" << std::endl; // change 8 to -stackpointer
        std::cout << "jr $31" << std::endl;
    }
};
/*
class Identifier_declaration : public Expression
{
private:
    std::string variable_id;
    int variable_address;

public:
    Identifier_declaration(std::string _variable_id) : variable_id(_variable_id) {}
    std::string fetch_variable_id()
    {
        return variable_id;
    }

    void translate(Context &context){
        cout << "mv $v0, 0" "# placeholder in Identifier_declaration"<< std::endl;
    }
   void translate_declaration(Context &context, variable &variable, type_declaration declarator_type, std::string dest_reg, int sp, int offset)
    {
        // type_declaration variable_type = variable.fetch_variable_type();
        int variable_addr = variable.fetch_variable_address();
        std::cout << "sw $fp " << variable_addr << "($sp)" << std::endl;
    }
    void translate(Context &context, variable &variable, type_declaration declarator_type, Expression *expression, std::string dest_reg, int sp, int offset)
    {
        context.allocate_stack();
        int variable_pointer = context.fetch_stack_pointer();
        int variable_addr = variable.fetch_variable_address();
        expression->translate(context);
        context.deallocate_stack();
        std::cout << "lw $8 " << variable_pointer << std::endl;
        std::cout << "sw $8 " << variable_addr << "(sp)" << std::endl;
    }

};
 */
#endif
