#ifndef STACK_H
#define STACK_H


#define MAX_STACK_LENGTH 500
#define EMPTY_STACK 13
#define MAX_NODES 30
#define MAX_LENGTH 1000
#define MAX_J_CONV_LENGTH 10000


typedef enum {
	compare,
	if_node,
	int_node,
	v_int,
	function,
	from_to, 
	for_node,
	while_node,
	read_node,
	show_node,
	v_string,
	string_node,
	v_var,
	set_node,
	call_function,
	op_int
} types;

struct Node {
	types type;
	char* j_conversion;
};


void addNode(struct Node* node);
struct Node* popNode();
void add_function_to_stack(struct Node* node);
char* getFunctions();
void configure_loop_node(struct Node* n, char* str, types type);
struct Node* create_node_function(char* ret, char* name);
struct Node* create_node_variable(char* name);
struct Node* create_node_string_var(char* name, char* value);
struct Node* create_node_if();
struct Node* create_node_for();
struct Node* create_node_while();
struct Node* create_node_read(char* str);
struct Node* create_node_print_string(char* str);
struct Node* create_node_int_print(int num);
struct Node* create_node_set_int(char* str);
struct Node* create_node_set_string(char* str, char* val);
struct Node* create_node_function_call(char* name);
struct Node* create_node_int_var(char* name, int value);
struct Node* create_node_new_var(char* str);
struct Node* create_node_from_to(char* name, int from, int to);
struct Node* create_node_from_tochar(char* name, int from, char* to);
struct Node* create_node_fromchar_tochar(char* name, char* from, char* to);
struct Node* create_node_cmp_symbol(char* sym);
struct Node* create_node_cmp_symbol_aux(char* sym);
struct Node* create_node_cmp(char* symbol, struct Node* left, struct Node* right);
struct Node* create_node_op(char* sym);
struct Node* create_node_parenthesis();
struct Node* create_node_int_stack(int value); 
struct Node* create_node_integer(int value);
struct Node* create_node_call_var(char* sym); 


#endif