%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

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
  double number;
  std::string *string;
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
%token T_FLOAT_VAL T_VARIABLE_VAL T_VARIABLE T_INTEGER_VAL
// Misc
%token SEMI_COLON COMMA COLON DECIMAL AMPERSAND EXLAIMATION TILDA HAT UPRIGHT_SLASH QUESTION_MARK PTR_OP
// Assign
%token EQUAL RIGHT_ASSIGN LEFT_ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN

%token T_IDENTIFIER 


/*----------------type--------------*/

%type <expr> function_definition global_declaration declaration
%type <number> T_FLOAT T_INTEGER
%type <string> T_VARIABLE T_LOG T_EXP T_SQRT FUNCTION_NAME T_IDENTIFIER


%start ROOT

%%

ROOT : EXPR { g_root = $1; }




integer : T_INTEGER { $$ = new Integer( $1 ); }

type : T_INT {$$ = new Types(INT); }



global_declaration : function_definition { $$ = $1; }
                    | declaration { $$ = $1; }
                    ;

function_definition : TYPE T_IDENTIFIER T_LBRACKET PARAMETER_LIST T_RBRACKET COMPOUND_STATEMENT
                    


type_specifier
	: VOID
	//| CHAR
	| INT
	//| FLOAT
	//| DOUBLE
	//| UNSIGNED
	//| TYPE_NAME
	;

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
