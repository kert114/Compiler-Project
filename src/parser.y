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
%token T_TIMES T_DIVIDE T_PLUS T_MINUS
// Logical
%token T_LOGICAL_AND T_LOGICAL_OR T_LOGICAL_RIGHT_SHIFT T_LOGICAL_LEFT_SHIFT
// Brackets
%token T_LBRACKET T_RBRACKET
// Loops
%token T_WHILE 
// IfElse
%token T_IF T_ELSE 
// Types
%token T_INT T_VOID
// Vars
%token T_FLOAT T_VARIABLE

/*----------------type--------------*/

%type <expr> EXPR TERM UNARY FACTOR
%type <number> T_FLOAT T_INTEGER
%type <string> T_VARIABLE T_LOG T_EXP T_SQRT FUNCTION_NAME 

%start ROOT

%%

ROOT : EXPR { g_root = $1; }





ADD_SUB_EXPR :  ADD_SUB_EXPR T_PLUS TERM { $$ = new AddOperator ($1, $3); }
    |   ADD_SUB_EXPR T_MINUS TERM {$$ = new SubOperator ($1, $3);}
    | TERM           { $$ = $1; }

TERM : TERM T_TIMES UNARY { $$ = new MulOperator ($1, $3); }
    | TERM T_DIVIDE UNARY { $$ = new DivOperator ($1, $3); } 
    | UNARY          { $$ = $1; }

UNARY : T_MINUS FACTOR { $$ = new NegOperator($2); }
      | FACTOR        { $$ = $1; }

FACTOR : T_INTEGER     { $$ = new Integer( $1 ); }
       | T_VARIABLE  { $$ = new Variable (*$1); }
       | T_LBRACKET ADD_SUB_EXPR T_RBRACKET { $$ = $2; }

integer : T_INTEGER { $$ = new Integer( $1 ); }

type : T_INT {$$ = new Types(INT); }




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
