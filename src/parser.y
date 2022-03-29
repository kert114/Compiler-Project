%code requires{
#include "ast/ast_expression.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_context.hpp"
#include "ast/ast_types.hpp"
#include <cassert>

  extern const std::vector<Expression*> *g_root; // A way of getting the AST out
  

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
	Expression *expr;
	double number;
	std::string *string;
	Declaration 	*declaration_node;
	Statement 		*statement_node;
	int 			int_num;
	std::vector<Expression*>* 	expr_list_vector;
	std::vector<Statement*>* 	statement_list_vector;
	std::vector<Declaration*>* 	declaration_list_vector;
}

/*---------------token-------------*/
// Arithmetic
%token ASTERIX R_SLASH PLUS MINUS PERCENT LESS_THAN GREATER_THAN GREATER_OR_EQUAL LESS_OR_EQUAL EQUAL_TO NOT_EQUAL DECREMENT_OP INCREMENT_OP
// Logical
%token T_LOGICAL_AND T_LOGICAL_OR T_LOGICAL_RIGHT_SHIFT T_LOGICAL_LEFT_SHIFT
// Brackets
%token L_BRACKET R_BRACKET R_SQUIRLY L_SQUARE R_SQUARE
// Loops
%token T_WHILE T_FOR T_DO TILDA L_SQUILY
// IfElse
%token T_IF T_ELSE T_CASE T_SWITCH T_BREAK
// Types
%token T_INT T_VOID T_DOUBLE T_CHAR T_LONG T_FLOAT T_SHORT T_ENUM T_SIZEOF T_CONTINUE T_DEFAULT T_STRUCT T_SIGNED T_UNSIGNED T_TYPEDEF T_VOLATILE T_RETURN
// Vars
%token T_FLOAT_VAL T_VARIABLE 
// Misc
%token SEMI_COLON COMMA COLON DECIMAL AMPERSAND EXCLAIMATION HAT UPRIGHT_SLASH QUESTION_MARK PTR_OP
// Assign
%token EQUAL RIGHT_ASSIGN LEFT_ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN

%token IDENTIFIER CONSTANT T_INTEGER_VAL



/*----------------type--------------*/

%type <expr_list_vector> translation_unit
%type <expr> external_declaration function_definition
%type <declaration_node> declaration 
%type <statement_node> statement return_statement compound_statement
%type <declaration_list_vector> declarations
%type <statement_list_vector> statements
%type <string> assignment_operator 
%type <expr> expression  logical_or_expression inclusive_or_expression unary_expression assignment_expression
%type <expr> exclusive_or_expression conditional_expression multiplicative_expression primary_expression
%type <expr> equality_expression relational_expression shift_expression additive_expression logical_and_expression and_expression
%type <string> IDENTIFIER MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN
%type <string> AND_ASSIGN XOR_ASSIGN OR_ASSIGN QUESTION_MARK T_LOGICAL_AND T_LOGICAL_OR HAT AMPERSAND EQUAL NOT_EQUAL LESS_THAN GREATER_THAN
%type <string> LESS_OR_EQUAL GREATER_OR_EQUAL T_LOGICAL_LEFT_SHIFT T_LOGICAL_RIGHT_SHIFT PLUS MINUS ASTERIX R_SLASH PERCENT INCREMENT_OP DECREMENT_OP T_SIZEOF
%type <string> EXCLAIMATION T_INT
%type <number> T_INTEGER_VAL


%start root

%%

root : translation_unit { g_root = $1; };

translation_unit  : external_declaration { $$ = new std::vector<Expression*>; $$->push_back($1); }
                  | translation_unit external_declaration { $$=$1; $$->push_back($2);}
				  ;

external_declaration	: function_definition { $$ = $1; }	//functions
                    	| declaration { $$ = $1; }			//global variables
						;

					  // int function without arguments
function_definition : T_INT IDENTIFIER L_BRACKET R_BRACKET compound_statement { std::cerr << "in func def\n";$$ = new function_declaration(*$2, $5); } 
                    | T_INT IDENTIFIER L_BRACKET T_INT IDENTIFIER COMMA T_INT IDENTIFIER R_BRACKET compound_statement { $$ = new function_declaration(*$2, $10, *$5, *$8 ); }
					; 

// Declarations
declarations  : declaration { std::cerr << "in first declarations\n"; $$ = new std::vector<Declaration*>; $$->push_back($1); }
			  | declarations declaration  { std::cerr << "in subsequent declarations\n"; $$=$1; $$->push_back($2);} // list of declarations
			  ;

declaration : T_INT IDENTIFIER SEMI_COLON  { $$ = new Declaration(*$2, NULL); } // int x;
			| T_INT IDENTIFIER EQUAL expression SEMI_COLON   { std::cerr << "in declaration\n";  $$ = new Declaration(*$2, $4); } // int x = 2*4;
			| IDENTIFIER EQUAL expression SEMI_COLON   {  $$ = new Declaration(*$1, $3); } // x = 2*4;
            ;


// Statements

statements : statement {$$ = new std::vector<Statement*>; $$->push_back($1); }
           | statements statement	{ $$=$1; $$->push_back($2);}
		   ;

statement : compound_statement { std::cerr << "in compound_statement\n"; $$ = $1; }
          | return_statement { std::cerr << "in return_statement\n"; $$ = $1; }    
		  ;      

compound_statement  : L_SQUILY R_SQUIRLY { $$ = new compound_statement_declaration(NULL, NULL); }
					| L_SQUILY statements R_SQUIRLY { $$ = new compound_statement_declaration(NULL, $2); }
					| L_SQUILY declarations R_SQUIRLY { $$ = new compound_statement_declaration($2, NULL); }
					| L_SQUILY declarations statements R_SQUIRLY { $$ = new compound_statement_declaration($2, $3); }
					;

return_statement : T_RETURN SEMI_COLON { std::cerr << "in return empty\n"; $$ = new return_statement_declaration(NULL); }
                 | T_RETURN expression SEMI_COLON { std::cerr << "in return expr\n"; $$ = new return_statement_declaration($2); }
				 ;

// operators

assignment_operator : EQUAL 
					| MUL_ASSIGN
					| DIV_ASSIGN
					| MOD_ASSIGN
					| ADD_ASSIGN
					| SUB_ASSIGN
					| LEFT_ASSIGN
					| RIGHT_ASSIGN
					| AND_ASSIGN
					| XOR_ASSIGN
					| OR_ASSIGN
					;

// Expressions

primary_expression  : IDENTIFIER {  std::cerr << "in primary_expr IDENTIFIER\n"; $$ = new Variable(*$1); };
	                | T_INTEGER_VAL  { std::cerr << "in primary_expr INT_VAL\n"; $$ = new Integer( $1 ); }
					| '(' expression ')' { $$ = $2; };
                    ;

expression 	: assignment_expression { $$ = $1; }
          	;

assignment_expression 	: conditional_expression { $$ = $1; }
	                    | unary_expression assignment_operator assignment_expression { $$ = new binary_expression($1, *$2, $3, true); }
	                    ;

conditional_expression  : logical_or_expression { $$ = $1; }
	                    | logical_or_expression QUESTION_MARK expression COLON conditional_expression  { $$ = new ternary_expression($1, $3, $5); }
	                	;

logical_or_expression : logical_and_expression { $$ = $1; }
	                    | logical_or_expression T_LOGICAL_OR logical_and_expression { $$ = new binary_expression($1, "||", $3); }
	                    ;

logical_and_expression : inclusive_or_expression { $$ = $1; }
	                      | logical_and_expression T_LOGICAL_AND inclusive_or_expression { $$ = new binary_expression($1, "&&", $3); }
	                      ;

inclusive_or_expression : exclusive_or_expression { $$ = $1; }
						| inclusive_or_expression UPRIGHT_SLASH exclusive_or_expression { $$ = new binary_expression($1, "|", $3); }
						;

exclusive_or_expression : and_expression { $$ = $1; }
						| exclusive_or_expression HAT and_expression { $$ = new binary_expression($1, "^", $3); }
						;

and_expression  : equality_expression { $$ = $1; }
	            | and_expression AMPERSAND equality_expression { $$ = new binary_expression($1, "&", $3); }
	            ;

equality_expression : relational_expression { $$ = $1; }
	                  | equality_expression EQUAL relational_expression { $$ = new binary_expression($1, "==", $3); }
	                  | equality_expression NOT_EQUAL relational_expression { $$ = new binary_expression($1, "!=", $3); }
	                  ;

relational_expression : shift_expression { $$ = $1; }
                      | relational_expression LESS_THAN shift_expression { $$ = new binary_expression($1, "<", $3); }
                      | relational_expression GREATER_THAN shift_expression { $$ = new binary_expression($1, ">", $3); }
                      | relational_expression LESS_OR_EQUAL shift_expression { $$ = new binary_expression($1, "<=", $3); }
                      | relational_expression GREATER_OR_EQUAL shift_expression { $$ = new binary_expression($1, ">=", $3); }
                      ;

shift_expression : additive_expression { $$ = $1; }
	                | shift_expression T_LOGICAL_LEFT_SHIFT additive_expression { $$ = new binary_expression($1, "<<", $3); }
	                | shift_expression T_LOGICAL_RIGHT_SHIFT additive_expression { $$ = new binary_expression($1, ">>", $3); }
	                ;

additive_expression   : multiplicative_expression { $$ = $1; }
	                  | additive_expression PLUS multiplicative_expression { $$ = new binary_expression($1, "+", $3); }
	                  | additive_expression MINUS multiplicative_expression { $$ = new binary_expression($1, "-", $3); }
	                  ;

multiplicative_expression : unary_expression { $$ = $1; }
                          | multiplicative_expression ASTERIX unary_expression { $$ = new binary_expression($1, "*", $3); }
                          | multiplicative_expression R_SLASH unary_expression { $$ = new binary_expression($1, "/", $3); }
                          | multiplicative_expression PERCENT unary_expression { $$ = new binary_expression($1, "%", $3); }
                          ;

unary_expression    : primary_expression { $$ = $1; }
  					| INCREMENT_OP unary_expression { $$ = new unary_expression($2, "++"); }
  					| DECREMENT_OP unary_expression { $$ = new unary_expression($2, "--"); }
  					| T_SIZEOF unary_expression { $$ = new unary_expression($2, "sizeof"); }
  					;

%%

const std::vector<Expression*>* g_root; // Definition of variable (to match declaration earlier)

const std::vector<Expression*>* parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
