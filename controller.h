#ifndef DMANAGER_H
#define DAMANGER_H


#define MAX_VARIABLES 124
#define MAX_FUNCTIONS 124

typedef enum {
	false,
	true
} bool;

unsigned int create_new_hash(char * key);
bool add_var(char* key);
bool contains_var(char * key);
void clear_variables();
bool contains_function(char* name);
bool add_function(char* name);
bool check_main_exist();
void printIDAlreadyCreated(char* id);
void to_ret_functions();
void printFunctionNotFound(char* name);

#endif