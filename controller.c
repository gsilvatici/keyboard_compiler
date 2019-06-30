#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "stack.h"
#include "outfile.h"


unsigned int vars_names[MAX_VARIABLES] = {0};
unsigned int functions_names[MAX_FUNCTIONS] = {0};

int functions_defined = 0;
int var_defined = 0;

// https://en.wikipedia.org/wiki/Jenkikns_hash_function
unsigned int create_new_hash(char *key){
    unsigned int hash, i;

    int counter = 0;
    while(key[counter] != '\0'){
    	counter++;
    }

    for(hash = i = 0; i < counter; ++i){
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

bool contains_var(char * id){

	unsigned int hash_var_name = create_new_hash(id);

	int i;
	for(i = 0 ; i < var_defined; i++){
		if( vars_names[i] == hash_var_name ){
			return true;
		}
	}
	return false;
}

bool add_var(char* key){

	if(!contains_var(key)){
		vars_names[var_defined] = create_new_hash(key);
		var_defined++;	
		return true;
	}else
		return false;
}

void clear_variables(){
	var_defined = 0;
}

bool contains_function(char* name){
	
	int hash = create_new_hash(name);
	int i;
	for( i = 0 ; i < functions_defined ; i++){
		if (functions_names[i] == hash){
			return true;
		}
	}

	return false;
}

bool add_function(char* name){

	if (contains_function(name)){
		return false;
	}

	int hash = create_new_hash(name);
	functions_names[functions_defined] = hash;
	functions_defined++;
	return true;

}

bool check_main_exist(){
	int i = 0;
	int hash_main = create_new_hash("main");

	for( i = 0 ; i < functions_defined ; i++){
		if( functions_names[i] == hash_main )
			return true;
	}
	return false;
}

void to_ret_functions(){
	outfput(getFunctions());
}
