#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_expression.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_types.hpp"

#include "stdio.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <cstdlib>
#include <typeinfo>

extern const Node* parse();
extern FILE* yyin;

#endif
