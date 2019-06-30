/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SKL = 258,
    FUNCTION = 259,
    CONST = 260,
    INTEGER_TYPE = 261,
    STRING_TYPE = 262,
    CALL = 263,
    IF = 264,
    FOR = 265,
    STARTENDF = 266,
    WHILE = 267,
    INTEGER = 268,
    ID = 269,
    TEXT = 270,
    TO = 271,
    PUT = 272,
    GET = 273,
    COMPARE = 274,
    ADD = 275,
    SUBSTRACT = 276,
    MULTIPLY = 277,
    DIVIDE = 278,
    MODULE = 279,
    EQUAL = 280,
    OR = 281,
    AND = 282,
    NOT = 283,
    GREATER = 284,
    LESSER = 285,
    UMINUS = 286
  };
#endif
/* Tokens.  */
#define SKL 258
#define FUNCTION 259
#define CONST 260
#define INTEGER_TYPE 261
#define STRING_TYPE 262
#define CALL 263
#define IF 264
#define FOR 265
#define STARTENDF 266
#define WHILE 267
#define INTEGER 268
#define ID 269
#define TEXT 270
#define TO 271
#define PUT 272
#define GET 273
#define COMPARE 274
#define ADD 275
#define SUBSTRACT 276
#define MULTIPLY 277
#define DIVIDE 278
#define MODULE 279
#define EQUAL 280
#define OR 281
#define AND 282
#define NOT 283
#define GREATER 284
#define LESSER 285
#define UMINUS 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "tla.y" /* yacc.c:1909  */

        int number;
        char *string;

#line 121 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
