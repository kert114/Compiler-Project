#ifndef ast_context_hpp
#define ast_context_hpp

#include <string>
#include <iostream>
#include <map>

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


class Context
{
	public:

		// Trackers and counters
		int stack_pointer = 0;
		int register_counter = 0;

    std::map<std::string, std::string> label_variables;
		std::map<std::string, std::string> label_declarations;


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

		int get_stack_pointer() { return stack_pointer; }

    void store_register(std::string register_name, int offset)
		{
			std::cout<<"sw "<<register_name<<" "<<offset<<"($30)"<< std::endl;
		}
};

#endif