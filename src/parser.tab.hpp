/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser.y"

  #include "ast.hpp"

  #include <cassert>

  extern const Node *root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

#line 62 "src/parser.tab.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ASTERIX = 258,
    R_SLASH = 259,
    PLUS = 260,
    MINUS = 261,
    PERCENT = 262,
    LESS_THAN = 263,
    GREATER_THAN = 264,
    GREATER_OR_EQUAL = 265,
    LESS_OR_EQUAL = 266,
    EQUAL_TO = 267,
    NOT_EQUAL = 268,
    DECREMENT_OP = 269,
    INCREMENT_OP = 270,
    T_LOGICAL_AND = 271,
    T_LOGICAL_OR = 272,
    T_LOGICAL_RIGHT_SHIFT = 273,
    T_LOGICAL_LEFT_SHIFT = 274,
    L_BRACKET = 275,
    R_BRACKET = 276,
    L_SQUIRLY = 277,
    R_SQUIRLY = 278,
    L_SQUARE = 279,
    R_SQUARE = 280,
    T_WHILE = 281,
    T_FOR = 282,
    T_DO = 283,
    T_IF = 284,
    T_ELSE = 285,
    T_CASE = 286,
    T_SWITCH = 287,
    T_BREAK = 288,
    T_INT = 289,
    T_VOID = 290,
    T_DOUBLE = 291,
    T_CHAR = 292,
    T_LONG = 293,
    T_FLOAT = 294,
    T_SHORT = 295,
    T_ENUM = 296,
    T_SIZEOF = 297,
    T_CONTINUE = 298,
    T_DEFAULT = 299,
    T_STRUCT = 300,
    T_SIGNED = 301,
    T_UNSIGNED = 302,
    T_TYPEDEF = 303,
    T_VOLATILE = 304,
    T_RETURN = 305,
    T_FLOAT_VAL = 306,
    T_VARIABLE = 307,
    T_INTEGER_VAL = 308,
    SEMI_COLON = 309,
    COMMA = 310,
    COLON = 311,
    DECIMAL = 312,
    AMPERSAND = 313,
    EXCLAIMATION = 314,
    TILDA = 315,
    HAT = 316,
    UPRIGHT_SLASH = 317,
    QUESTION_MARK = 318,
    PTR_OP = 319,
    EQUAL = 320,
    RIGHT_ASSIGN = 321,
    LEFT_ASSIGN = 322,
    ADD_ASSIGN = 323,
    SUB_ASSIGN = 324,
    MUL_ASSIGN = 325,
    DIV_ASSIGN = 326,
    MOD_ASSIGN = 327,
    AND_ASSIGN = 328,
    XOR_ASSIGN = 329,
    OR_ASSIGN = 330,
    IDENTIFIER = 331,
    CONSTANT = 332,
    parameter_types = 333,
    abstract_declarator = 334,
    pointer = 335,
    assignment_operator = 336
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "src/parser.y"

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

#line 174 "src/parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_TAB_HPP_INCLUDED  */
