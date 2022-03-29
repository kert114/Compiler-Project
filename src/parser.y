%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Node *root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
	const Expression *expr;
	const Node *node;
	double number;
	std::string *string;
	Declarator 		*declarator_node;
	Declaration 	*declaration_node;
	Statement 		*statement_node;
	Expression 		*expression_node;
	type_declaration *type_node;
	int 			int_num;
	std::vector<Expression*>* 	argument_list_vector;
	std::vector<Statement*>* 	statement_list_vector;
	std::vector<Declaration*>* 	declaration_list_vector;
	std::vector<Declarator*>* 	declarator_list_vector;

	std::vector<Expression*>* 	initialisation_list;
}

/*---------------token-------------*/
// Arithmetic
%token ASTERIX R_SLASH PLUS MINUS PERCENT LESS_THAN GREATER_THAN GREATER_OR_EQUAL LESS_OR_EQUAL EQUAL_TO NOT_EQUAL DECREMENT_OP INCREMENT_OP
// Logical
%token T_LOGICAL_AND T_LOGICAL_OR T_LOGICAL_RIGHT_SHIFT T_LOGICAL_LEFT_SHIFT
// Brackets
%token L_BRACKET R_BRACKET L_SQUIRLY R_SQUIRLY L_SQUARE R_SQUARE
// Loops
%token T_WHILE T_FOR T_DO
// IfElse
%token T_IF T_ELSE T_CASE T_SWITCH T_BREAK
// Types
%token T_INT T_VOID T_DOUBLE T_CHAR T_LONG T_FLOAT T_SHORT T_ENUM T_SIZEOF T_CONTINUE T_DEFAULT T_STRUCT T_SIGNED T_UNSIGNED T_TYPEDEF T_VOLATILE T_RETURN
// Vars
%token T_FLOAT_VAL T_VARIABLE T_INTEGER_VAL
// Misc
%token SEMI_COLON COMMA COLON DECIMAL AMPERSAND EXCLAIMATION TILDA HAT UPRIGHT_SLASH QUESTION_MARK PTR_OP
// Assign
%token EQUAL RIGHT_ASSIGN LEFT_ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN

%token IDENTIFIER CONSTANT

%token parameter_types abstract_declarator pointer assignment_operator


/*----------------type--------------*/

%type <expr> function_definition external_declaration declaration compound_statement declarations statements statement return_statement parameters
%type <expr> primary_expression translation_unit type_specifier parameter_types
%type <expr> assignment_expression argument_expressions_list init_declarators
%type <expr> identifier_list declarator parameter_declaration direct_declarator abstract_declarator pointer init_declarator
%type <expr> IDENTIFIER initializer initializer_list
%type <expr> expression conditional_expression logical_or_expression inclusive_or_expression unary_expression assignment_operator 
%type <expr> equality_expression relational_expression shift_expression additive_expression multiplicative_expression cast_expression postfix_expression
%type <expr> exclusive_or_expression
%type <expr> T_INT T_FLOAT 
%type <number> T_FLOAT_VAL T_INTEGER_VAL
%type <string> T_VARIABLE FUNCTION_NAME  


%start root

%%

root : translation_unit { g_root = $1; };

translation_unit  : external_declaration { $$ = $1; }
                  | translation_unit external_declaration { $$ = new translation_unit_declaration ($1,$2)}
				  ;


function_definition : type_specifier IDENTIFIER L_BRACKET declarator R_BRACKET compound_statement{ ( $$ = new function_declaration($1, *$2, $4, $6); }
                    | type_specifier IDENTIFIER L_BRACKET R_BRACKET compound_statement{ ( $$ = new function_declaration($1, *$2, $5); }
                    ;

// identifiers 

identifier_list : IDENTIFIER { $$ = $1; }
	              | identifier_list COMMA IDENTIFIER
	              ;

// declarations

external_declaration	: function_definition { $$ = $1; }
                    	| declaration { $$ = $1; }
						;

declaration : type_specifier SEMI_COLON  { $$ = $1; }
            | type_specifier init_declarators SEMI_COLON
            ;

declarator  : pointer direct_declarator
	        | direct_declarator { $$ = $1; }
          	;


declarations 	: declaration { $$ = new std::vector<Declaration*>(1,$1); }
            	| declarations COMMA declaration {}   
				;

direct_declarator   : IDENTIFIER { $$ = $1; }
	                | L_BRACKET declarator R_BRACKET { $$ = $2; }
	                | direct_declarator L_SQUARE constant_expression R_BRACKET
	                | direct_declarator L_BRACKET parameters R_BRACKET
	                | direct_declarator L_BRACKET identifier_list R_BRACKET
	                | direct_declarator L_BRACKET R_BRACKET { $$ = $1; }
					| direct_declarator L_SQUARE R_SQUARE { $$ = $1; }
	                ;


init_declarators    : init_declarator
					| init_declarators COMMA init_declarator
					;


init_declarator : declarator
				| declarator EQUAL initializer
				;

initializer 	: assignment_expression
				| L_SQUIRLY initializer_list R_SQUIRLY
				| L_SQUIRLY initializer_list COMMA R_SQUIRLY
				;

initializer_list 	: initializer
					| initializer_list COMMA initializer
					;
// Parameters

parameters  : parameter_declaration { $$ = new std::vector<Declaration*>(1, $1); }
	        | parameters COMMA parameter_declaration
            | { $$ = NULL; }
	        ;

parameter_declaration : type_specifier declarator { $$ = new Declaration(*$1, new std::vector<Declarator*>(1, $2)); }
                      ;


 


// Statements 

compound_statement  : L_SQUIRLY R_SQUIRLY { $$ = new compound_statement_declaration(); }
					| L_SQUIRLY statements R_SQUIRLY { $$ = new compount_statement_declaration($2, NULL); }
					| L_SQUIRLY declarations R_SQUIRLY { $$ = new compount_statement_declaration(NULL, $2); }
					| L_SQUIRLY statements declarations R_SQUIRLY { $$ = new compount_statement_declaration($2, $3); }


statements : statement {$$ = new std::vector<Statement*>(1,$1); }
           | statements statement	

statement : compound_statement { $$ = $1; }
          | return_statement { $$ = $1; }          



jump_statement 	: T_CONTINUE SEMI_COLON
				| T_BREAK SEMI_COLON
				;


return_statement : T_RETURN SEMI_COLON { new return_statement(); }
                 | T_RETURN argument_expressions_list SEMI_COLON { new return_statement($2); }

// operators

unary_operator 	: AMPERSAND
				| ASTERIX
				| PLUS
				| MINUS
				| TILDA
				| EXCLAIMATION
				;


// Types

type_specifier : T_INT { $$ = new type_declaration(INT); }
	/*			| VOID
/*				| CHAR
				| SHORT
				| LONG
				| FLOAT
				| DOUBLE
				| SIGNED
				| UNSIGNED
				| struct_or_union_specifier
				| enum_specifier
				| TYPE_NAME*/
				;
				


// Expressions


expression 	: assignment_expression { $$ = $1; }
	        | expression COMMA assignment_expression
          	;

assignment_expression 	: conditional_expression { $$ = $1; }
	                    | unary_expression assignment_operator assignment_expression
	                    ;


conditional_expression  : logical_or_expression { $$ = $1; }
	                    | logical_or_expression QUESTION_MARK expression COLON conditional_expression
	                	;


argument_expressions_list : assignment_expression {$$ = new std::vector<Expression*>(1,$1); }
                          | argument_expressions_list COMMA assignment_expression
                          ;



constant_expression : conditional_expression 
	            	;


primary_expression  : IDENTIFIER { $$ = new Identifier_declaration(*$1); };
	                | CONSTANT
	                | T_VARIABLE
	                | L_BRACKET expression R_BRACKET
                    ;




///*

	                  
 // expressions - logical 
// /*
logical_and_expression : inclusive_or_expression
	                      | logical_and_expression T_LOGICAL_AND inclusive_or_expression
	                      ;

logical_or_expression : logical_and_expression
	                    | logical_or_expression T_LOGICAL_OR logical_and_expression
	                    ;

exclusive_or_expression : and_expression
						| exclusive_or_expression HAT and_expression
						;

inclusive_or_expression : exclusive_or_expression
						| inclusive_or_expression UPRIGHT_SLASH exclusive_or_expression
						;

and_expression  : equality_expression
	            | and_expression AMPERSAND equality_expression
	            ;

equality_expression : relational_expression
	                  | equality_expression EQUAL relational_expression
	                  | equality_expression NOT_EQUAL relational_expression
	                  ;

relational_expression : shift_expression
                      | relational_expression LESS_THAN shift_expression
                      | relational_expression GREATER_THAN shift_expression
                      | relational_expression LESS_OR_EQUAL shift_expression
                      | relational_expression GREATER_OR_EQUAL shift_expression
                      ;

shift_expression : additive_expression
	                | shift_expression T_LOGICAL_LEFT_SHIFT additive_expression
	                | shift_expression T_LOGICAL_RIGHT_SHIFT additive_expression
	                ;
                  
additive_expression   : multiplicative_expression
	                  | additive_expression PLUS multiplicative_expression
	                  | additive_expression MINUS multiplicative_expression
	                  ;

multiplicative_expression : cast_expression
                          | multiplicative_expression ASTERIX cast_expression
                          | multiplicative_expression R_SLASH cast_expression
                          | multiplicative_expression PERCENT cast_expression
                          ;

cast_expression   : unary_expression
	             // | '(' type_name ')' cast_expression
	              ;

unary_expression    : postfix_expression
  					| INCREMENT_OP unary_expression
  					| DECREMENT_OP unary_expression
  					| unary_operator cast_expression
  					| T_SIZEOF unary_expression
  					// | T_SIZEOF '(' type_name ')'
  					;

postfix_expression  : primary_expression
					| postfix_expression L_SQUARE expression R_SQUARE
					| postfix_expression L_BRACKET R_BRACKET
					| postfix_expression L_BRACKET argument_expressions_list R_BRACKET
					| postfix_expression DECIMAL IDENTIFIER
					| postfix_expression PTR_OP IDENTIFIER
					| postfix_expression INCREMENT_OP
					| postfix_expression DECREMENT_OP
					;




%%

const Node *root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  root=0;
  yyparse();
  return root;
}
