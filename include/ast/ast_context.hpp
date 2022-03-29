#ifndef ast_context_hpp
#define ast_context_hpp

#include <string>
#include <iostream>
#include <map>
#include <stack>

#include "ast_types.hpp"
#include "ast_expression.hpp"

/*struct registers
{
  int usedRegs[32] =
  { 1, // zero
    1, // at Assembler Temporary
    1, 1, // v0-v1 function results
    1, 1, 1, 1, // a0-a3 function arguments
    0, 0, 0, 0, 0, 0, 0, 0, // tempoary registers
    1, 1, 1, 1, 1, 1, 1, 1, // s0-s7 saved
    0, 0, // temporary
    1, 1, // reserved for kernal
    1, //global pointer
    1, // stack pointer
    1, // frame pointer
    1}; //return address

  void useReg(int i); // Register is now being used
  void freeReg(int i); // Register is no longer being used
  int allocate(); // Returns empty register, -1 if no registers are available (Helper function for context)
};*/

class variable
{
private:
  std::string variable_value;
  type_declaration variable_type;
  int variable_address;
public:
  variable(std::string _variable_value, type_declaration _variable_type, int _variable_address)
      : variable_value(_variable_value), variable_type(_variable_type), variable_address(_variable_address) {}

  int fetch_variable_address()
  {
    return variable_address;
  }
  type_declaration fetch_variable_type()
  {
    return variable_type;
  }
};

typedef std::map<std::string, variable *> type_mapping;

class Context
{
private:
  int stack_pointer = 0;
  int register_counter = 0;

  std::stack<type_mapping *> context_scope_stack_tracker;
  std::stack<int> context_scope_frame_pointer;

public:
  std::map<std::string, int> label_variables;
  std::map<std::string, std::string> label_declarations;

  void variable_val(std::string variable_id, auto variable_value)
  {
    if(label_variables.count(variable_id)==0){
      label_variables[variable_id];
    };
    label_variables.find(variable_id)->second = variable_value;
  }

  int get_variable_offset(std::string variable_id)
  {

    return label_variables[variable_id];
  }

  void allocate_stack()
  {
    register_counter++;
    stack_pointer -= 8;
  }

  void deallocate_stack()
  {
    if (register_counter != 0)
    {
      stack_pointer += 8;
      register_counter--;
    }
  }

  int fetch_stack_pointer()
  {
    return stack_pointer;
  }

  void store_register(std::string register_name, int offset)
  {
    std::cout << "sw " << register_name << ", " << offset << "($sp)" << std::endl;
  }
};

class Node
{
public:
  virtual ~Node()
  {
  }

  virtual void translate(
      Context &context) const
  {
    std::cerr << "Ast_node.hpp: 'compile' not implemented" << std::endl;
  }
};

typedef const Node *Node_Ptr;

#endif