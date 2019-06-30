all:
	yacc -d tla.y
	lex tla.l

	gcc -o tla lex.yy.c y.tab.c -ly controller.c stack.c outfile.c handler.c 

