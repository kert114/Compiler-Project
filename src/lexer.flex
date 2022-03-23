%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%%
/*------Types-----*/
"int"             { return T_INT; }
"void"            { return T_VOID; }
"char"            { return T_CHAR; }
"double"          { return T_DOUBLE; }
"enum"            { return T_ENUM; }
"float"           { return T_FLOAT; }
"long"            { return T_LONG; }
"short"           { return T_SHORT; }
"sizeof"          { return T_SIZEOF; }
"continue"        { return T_CONTINUE; }
"default"         { return T_DEFAULT; }
"struct"          { return T_STRUCT; }
"signed"          { return T_SIGNED; }
"typedef"         { return T_TYPEDEF; }
"unsigned"        { return T_UNSIGNED; }
"volatile"        { return T_VOLATILE; }
"return"          { return T_RETURN; }

/*------------IFELSE------------*/
"if"            { return T_IF; }
"else"          { return T_ELSE; }
"break"           { return T_BREAK; }
"case"            { return T_CASE; }
"switch"          { return T_SWITCH; }

/*-----------LOOPS--------------*/
"while"         { return T_WHILE; }
"for"           { return T_FOR; }
"do"              { return T_DO; }

{L}({L}|{D})*          { yylval.string=new std::string(yytext); return T_IDENTIFIER; }

{D}+{IS}?  {yylval.number=strtod(yytext, 0); return T_INTEGER_VAL; }
0[xX]{H}+{IS}?  {yylval.number=strtod(yytext, 0); return T_INTEGER_VAL; }
0{D}+{IS}?  {yylval.number=strtod(yytext, 0); return T_INTEGER_VAL; }
{D}+{E}{FS}? { yylval.number=strtod(yytext, 0); return T_FLOAT_VAL; }
{D}*"."{D}+({E})?{FS}? { yylval.number=strtod(yytext, 0); return T_FLOAT_VAL; }
{D}+"."{D}*({E})?{FS}? { yylval.number=strtod(yytext, 0); return T_FLOAT_VAL; }
L?\"(\\.|[^\\"])*\"   { yylval.string=new std::string(yytext); return T_VARIABLE_VAL; }

">>="			  { return RIGHT_ASSIGN; }
"<<="			  { return LEFT_ASSIGN; }
"+="			  { return ADD_ASSIGN; }
"-="			  { return SUB_ASSIGN; }
"*="			  { return MUL_ASSIGN; }
"/="			  { return DIV_ASSIGN; }
"%="			  { return MOD_ASSIGN; }
"&="			  { return AND_ASSIGN; }
"^="			  { return XOR_ASSIGN; }
"|="			  { return OR_ASSIGN; }
">>"			  { return T_LOGICAL_RIGHT_SHIFT; }
"<<"			  { return T_LOGICAL_LEFT_SHIFT; }
"++"			  { return INCREMENT_OP; }
"--"			  { return DECREMENT_OP; }
"->"			  { return PTR_OP; }
"&&"			  { return T_LOGICAL_AND; }
"||"			  { return T_LOGICAL_OR; }
"<="			  { return LESS_OR_EQUAL; }
">="			  { return GREATER_OR_EQUAL; }
"=="			  { return EQUAL_TO; }
"!="			  { return NOT_EQUAL; }
";"			    { return SEMI_COLON; }
("{"|"<%")	{ return L_SQUILY; }
("}"|"%>")	{ return R_SQUIRLY; }
","			    { return COMMA; }
":"			    { return COLON; }
"="			    { return EQUAL; }
"(" 		  	{ return L_BRACKET; }
")"	    		{ return R_BRACKET; }
("["|"<:")	{ return L_SQUARE; }
("]"|":>")	{ return R_SQUARE; }
"." 			  { return DECIMAL; }
"&"   			{ return AMPERSAND; }
"!"	    		{ return EXCLAIMATION; }
"~"		    	{ return TILDA; }
"-"			    { return MINUS; }
"+"  			  { return PLUS; }
"*"	    		{ return ASTERIX; }
"/"		    	{ return R_SLASH; }
"%"			    { return PERCENT; }
"<"   			{ return LESS_THAN; }
">"		    	{ return GREATER_THAN; }
"^"   			{ return HAT; }
"|"		    	{ return UPRIGHT_SLASH; }
"?"	    		{ return QUESTION_MARK; }

[ \t\r\n]+	{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}