%define parse.error verbose
%locations

%{
#include <stdio.h>
#include <stdlib.h>

#include "outfile.h"
#include "handler.h"

extern int yylex();
void yyerror(const char *s);

int line;

%}

%union 
{
        int number;
        char *string;
}

%token SKL FUNCTION CONST
%token INTEGER_TYPE STRING_TYPE 
%token CALL
%token IF FOR STARTENDF WHILE


%token <number> INTEGER
%token <string> ID
%token <string> TEXT

%token TO
%token PUT
%token GET
%token COMPARE


%left ADD SUBSTRACT MULTIPLY DIVIDE MODULE
%right EQUAL
%left OR AND NOT
%left GREATER LESSER

%right UMINUS
%start START



%%

START: 				SKL FUNCTIONS	 	{ 	
													return handle_main();
												}
		;

FUNCTIONS: 			FUNCT FUNCTIONS
				| 	FUNCT
				;

FUNCT:		 FUNCTION ID BODY	{
												line = @1.first_line;
												if (!handle_funDeclaration($2))
													return false;
											}

			;

BODY:		STARTENDF STATEMENTS STARTENDF
 			|	STARTENDF STARTENDF
 			;

STATEMENTS:		DECLARE_VAR
				| STIF
				| STFOR
				| STWHILE
				| STREAD
				| STPRINT
				| CHANGE_VAR
				| STFUNCTION
				| STCONST
				| DECLARE_VAR STATEMENTS
				| STIF STATEMENTS
				| STFOR STATEMENTS
				| STWHILE STATEMENTS
				| STREAD STATEMENTS
				| STPRINT STATEMENTS
				| CHANGE_VAR STATEMENTS
				| STFUNCTION STATEMENTS
				| STCONST STATEMENTS
				;



DECLARE_VAR: 	STRING_TYPE ID EQUAL TEXT ','			{
														line = @1.first_line;
														if (!handle_string_varDeclaration($2, $4))	
															return false;
													}
													
				| INTEGER_TYPE ID EQUAL INT_OPS ',' 	{ 		
														line = @1.first_line;
														if (!handle_int_varDeclaration($2))
															return false;
													}
				;


STIF:		IF ',' BOOLEANS ',' BODY	{ 
											handle_if();
 										}
			;

STFOR:		FOR COND_FOR BODY		{ 
										handle_for();
									}
			;

STWHILE:	WHILE ',' BOOLEANS ',' BODY 	{ 
												handle_while();
			;								}


STREAD:		GET ID ',' 	{
													line = @1.first_line; 
													if (!handle_stdRead($2))
													return false;
												}
			;

STPRINT:	PUT ID ','					 	{
													line = @1.first_line;
													if (!handle_var_stdWrite($2))
														return false;
												}
			
			| PUT INTEGER ',' 				{ 
													handle_int_stdWrite($2);
												}
			
			| PUT TEXT  ','					{ 	
													handle_string_stdWrite($2);													
												}
			
			;


CHANGE_VAR: 	ID EQUAL INT_OPS ','	{ 	
										line = @1.first_line;
										if (!handle_int_set($1))
											return false;
									}
				
				| ID EQUAL TEXT ','	{	
										line = @1.first_line;
										if (!handle_string_set($1, $3))
											return false;
									}
				;

STFUNCTION:	CALL ID ','	{
							line = @1.first_line;
							if (!handle_funCall($2))
								return false;
						}

STCONST: 	CONST ID INTEGER ','	{
										line = @1.first_line;
 										if (!handle_constInteger($2, $3))
 											return false;
 									}
 
	


COND_FOR: 	',' ID EQUAL INTEGER TO INTEGER ',' 	{ 
													handle_condFor($2,$4,$6);
												}
			
			| ',' ID EQUAL INTEGER TO ID ',' 	{ 	
													line = @1.first_line;
													if (!handle_condFor_varLimit($2,$4,$6))
														return false;

												}
			
			| ',' ID EQUAL ID TO ID ',' 			{ 	
													line = @1.first_line;
													if (!handle_condFor_allVar($2, $4, $6))
														return false;
												}
			;



INT_OPS:		TYPE ADD INT_OPS			{
												handle_int_op("+");
											}
				
				| TYPE SUBSTRACT INT_OPS			{
												handle_int_op("-");
											}
				
				| TYPE MULTIPLY INT_OPS			{
												handle_int_op("*");
											}
				
				| TYPE DIVIDE INT_OPS			{
												handle_int_op("/");
											}
				
				| TYPE MODULE INT_OPS			{
												handle_int_op("%");
											}
				
				| ',' INT_OPS ','			{
												handle_parenthesis();
											}

				| TYPE
				
				;
				
TYPE:			INTEGER 					{
												handle_int($1);
											}				

				| ID 						{
												handle_var($1);
											}
				;

BOOLEANS:	NOT ',' BOOL_CONDITION ',' 									{ handle_booleans("!"); } 
			| 	',' BOOL_CONDITION ',' AND ',' BOOL_CONDITION ','		{ handle_booleans("&&"); }
			| 	',' BOOL_CONDITION ',' OR ',' BOOL_CONDITION ','		{ handle_booleans("||"); }
			|	',' BOOL_CONDITION ','
			|	 BOOL_CONDITION
			;
       
BOOL_CONDITION: 
				INTEGER GREATER INTEGER 			{
													handle_int_cmp(">", $1, $3);
												}
				
				| INTEGER LESSER INTEGER  			{
													handle_int_cmp("<", $1, $3);
												}
				
				| INTEGER COMPARE INTEGER 		{
													handle_int_cmp("==", $1, $3);
												}
				
				| ID GREATER INTEGER 				{	
													line = @1.first_line;			
													if (!handle_int_var_cmp(">", $1, $3))
														return false;
												}
				
				| ID LESSER INTEGER 				{
													line = @1.first_line;			
													if (!handle_int_var_cmp("<", $1, $3))
														return false;
												} 
				
				| ID COMPARE INTEGER 			{
													line = @1.first_line;				
													if (!handle_int_var_cmp("==", $1, $3))
														return false;
												}
				
				| ID GREATER ID 					{ 
													line = @1.first_line;				
													if (!handle_var_var_cmp(">", $1, $3))
														return false;
												} 
				
				| ID LESSER ID 					{
													line = @1.first_line;				
													if (!handle_var_var_cmp("<", $1, $3))
														return false;
												} 
				
				| ID COMPARE ID 					{
													line = @1.first_line;				
													if (!handle_var_var_cmp("==", $1, $3))
														return false;
												}
				
				| INTEGER GREATER ID 				{
													line = @1.first_line;				
													if (!handle_int_var_cmp(">", $3, $1))
														return false;
												}  
				
				| INTEGER LESSER ID 				{
													line = @1.first_line;				
													if (!handle_int_var_cmp("<", $3, $1))
														return false;
												} 
				
				| INTEGER COMPARE ID 			{
													line = @1.first_line;				
													if (!handle_int_var_cmp("==", $3, $1))
														return false;
												}
				;		


%%

int yywrap()
{
        return 1;
} 

int main() {

   	outfcreate("out.java");
   	outfput("import java.util.Scanner;\n");
	outfput("public class out {\n\n");

	int valor = yyparse();

    if (valor != false){
    	to_ret_functions();
    } else {
    	outfput("public static void main(String[] args) {}\n");
    }

    outfput("}\n");
    outfclose();  

} 