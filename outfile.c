#include <stdio.h>
#include "outfile.h"

FILE * file;

void outfcreate(char* name){
	file = fopen(name, "w");
}

void outfput(char* str){
	fprintf(file, "%s", str);
}

void outfclose(){
	fclose(file);
}
