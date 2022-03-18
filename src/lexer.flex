%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

%%
/*------Types-----*/
"int"             { return T_INT; }
"void"            { return T_VOID; }

/*-------------ARITHMETIC---------*/
[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }

/*-------------LOGICAL-----------*/
[&][&]          { return T_LOGICAL_AND; }
[|][|]          { return T_LOGICAL_OR; }
[>][>]          { return T_LOGICAL_RIGHT_SHIFT; }
[<][<]          { return T_LOGICAL_LEFT_SHIFT; }

/*------------IFELSE------------*/
"if"            { return T_IF; }
"else"          { return T_ELSE; }

/*-----------LOOPS--------------*/
"while"         { return T_WHILE; }

[(]             { return T_LBRACKET; }
[)]             { return T_RBRACKET; }

log             { return T_LOG; }
exp             { return T_EXP; }
sqrt            { return T_SQRT; }

[0-9]+  {yylval.number=strtod(yytext, 0); return T_INTEGER}
[0-9]+([.][0-9]*)? { yylval.number=strtod(yytext, 0); return T_FLOAT; }
[a-zA-Z]+[a-zA-Z0-9]*          { yylval.string=new std::string(yytext); return T_VARIABLE; }

[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}