#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handler.h"
#include "stack.h"


int extern line;


bool handle_main() {
	if (main_exist()){
		handle_compile_success();
		return true;

	} else{
		handle_main_missing();
		return false;
	}
}

bool handle_funDeclaration(char * id) {
	struct Node* function_node = create_node_function("void", id);
	if (!add_function(id)) {
		handle_funRep(id);
		return false;
	}
	
	add_function_to_stack(function_node);
	return true;
}

//VARDECLARATION handle
bool handle_string_varDeclaration(char * id, char * string) {
	if (!contains_var(id)) {
		create_node_string_var(id, string); 
		return true;
	}
	handle_varRep(id);
	return false;
}

bool handle_int_varDeclaration(char * id) {
	if (!contains_var(id)) {
		create_node_variable(id);
		return true;
	}
	handle_varRep(id);
	return false;
}



//IF handle
void handle_if() {
	create_node_if();
}


//FOR handle
void handle_for() {
	create_node_for();
}

//WHILE handle
void handle_while() {
	create_node_while();
}


//READ handle
bool handle_stdRead(char * id) {
	if (contains_var(id)) {
		create_node_read(id);
		return true;
	}
	handle_var_undefined(id);
	return false;
}

//PRINT handle
bool handle_var_stdWrite(char * id) {
	if (contains_var(id)) {
		create_node_print_string(id);
		return true;
	}
	handle_var_undefined(id);
	return false;
}

void handle_int_stdWrite(int value) {
	create_node_int_print(value);
}

void handle_string_stdWrite(char * string) {
	create_node_print_string(string);
}

//CHANGE_VAR handle
bool handle_int_set(char * id) {
	if (contains_var(id)){
		create_node_set_int(id);
		return true;
	} 
	handle_var_undefined(id);
	return false;
}

bool handle_string_set(char * id, char * string) {
	if (contains_var(id)){
		create_node_set_string(id, string);
		return true;
	} 
	handle_var_undefined(id);
	return false;
}

//CALL handle
bool handle_funCall(char * id) {
	if (contains_function(id)) {
		create_node_function_call(id);
		return true;
	}
	handle_fun_undefined(id);
	return false;
}

//CONSTANT handle
bool handle_constInteger(char * id, int value) {
	if (!contains_var(id)){
		create_node_int_var(id, value);
		return true;
	} 
	handle_var_undefined(id);
	return false;
}

//CONDFOR handle
 void handle_condFor(char * id, int value, int limit) {
 	create_node_from_to(id, value, limit);
 }

bool handle_condFor_varLimit(char * id, int value, char * var_limit) {
 	if (!contains_var(var_limit)){
		handle_var_undefined(var_limit);
		return false;
	}
	create_node_from_tochar(id, value, var_limit);
	return true;
} 

bool handle_condFor_allVar(char * id, char * var_value, char * var_limit) {
	if (!contains_var(var_limit)){
		handle_var_undefined(var_limit);
		return false;
	}
	if (!contains_var(var_value)){
		handle_var_undefined(var_value);
		return false;
	}
	create_node_fromchar_tochar(id, var_value, var_limit);
}

//BOOLEANS handle
void handle_booleans(char * symbol){
	if( strcmp("!", symbol) == 0 ){
		create_node_cmp_symbol("!");
	}else{
		create_node_cmp_symbol_aux(symbol);	
	}
}

//INTOPS handle
void handle_int_op(char * op) {
	create_node_op(op);
}

void handle_parenthesis() {
	create_node_parenthesis();
}

//TYPE handle
void handle_int(int value) {
	create_node_integer(value);
}

bool handle_var(char * id) {
	if (contains_var(id)) {
		create_node_call_var(id);
		return true;
	}
	handle_var_undefined(id);
	return false;
}

//CMP handle
void handle_int_cmp(char * logic_op, int val1, int val2) {
	create_node_cmp(logic_op, create_node_int_stack(val1), create_node_int_stack(val2));
}

bool handle_int_var_cmp(char * logic_op, char * id, int value) {
	if (!contains_var(id)) {
		handle_var_undefined(id); 
		return false;
	}
	create_node_cmp(logic_op, create_node_new_var(id), create_node_int_stack(value));
	return true;
}

bool handle_var_var_cmp(char * logic_op, char * id1, char * id2) {
	if (!contains_var(id1)) {
		handle_var_undefined(id1); 
		return false;
	}
	if (!contains_var(id2)) {
		handle_var_undefined(id2); 
		return false;
	}
	create_node_cmp(logic_op, create_node_new_var(id1), create_node_new_var(id2));
	return true;
}

//prints
void handle_fun_undefined(char* function_name){
	printf("Error at line %d : Function '%s' not defined\n", line, function_name);
}

void handle_funRep(char * id) {
	printf("Error at line %d : Function '%s' already defined previously\n", line, id);
}

void handle_var_undefined(char* id){
	printf("Error at line %d : Variable '%s' undefined\n",line, id);
}

void handle_varRep(char* id){
	printf("Error at line %d : Variable '%s' already exist\n",line, id);
}

void handle_compile_success() {
	printf("Compiled successfuly!\n");
}

void handle_main_missing() {
	printf("Main method not founded\n");
}


///
///
///

