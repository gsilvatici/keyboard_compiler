%option yylineno

%{
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
	#include <stdio.h>
	#include <string.h>
    #include "y.tab.h"
%}

alpha [A-Za-z]
digit [0-9]

%%

[\t \n]

skl 		return SKL;
for			return FOR;
if			return IF;
whi 		return WHILE;
fun 		return FUNCTION;

int			return INTEGER_TYPE;
str			return STRING_TYPE;

go 			return CALL;
con 		return CONST;

\.\. 		return STARTENDF;

eq 			return EQUAL;
put			return PUT;
get			return GET;
to 			return TO;

cmp			return COMPARE;

add			return ADD;
sub			return SUBSTRACT;
mul			return MULTIPLY;
div 		return DIVIDE;
mod			return MODULE;

gre 		return GREATER;
les			return LESSER;
and  		return AND;
or 			return OR;
not  		return NOT;


{digit}+	{
			yylval.number = atoi(yytext);
			return INTEGER;
			}

[a-zA-Z][a-zA-Z0-9]* 	{
						yylval.string = strdup(yytext);
						return ID;
						}

[\.][a-zA-Z0-9?! ]*	{
						yylval.string = strdup(yytext);
						return TEXT;
						}

.			return yytext[0];

%%

void yyerror(const char *str)
{
    fprintf(stderr,"Error at line %d : %s\n",yylineno, str);
}
