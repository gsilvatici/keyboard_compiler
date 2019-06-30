#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "controller.h"


struct Node* stack[MAX_STACK_LENGTH];
int current_pos = 0;

struct Node* functions[MAX_FUNCT_LENGTH];
int p_functions = 0;

void addNode(struct Node* node){
	stack[current_pos] = node;
	current_pos++;
}

struct Node* popNode(){
	current_pos--;
	return stack[current_pos];
}

void add_function_to_stack(struct Node* node){
	functions[p_functions] = node;
	p_functions++;
}

char* getFunctions(){

	char* res = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	int i = 0;
	int p = p_functions;

	while( i != p){
		sprintf(res, "%s %s\n",res, functions[i]->j_conversion);
		i++;
	}

	return res;
}

//new function
struct Node* create_node_function(char* ret, char* name){ 
	
	struct Node* n = malloc(sizeof(struct Node));
	n->type = function; 
	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	if (strcmp(name,"main") == 0 ){
		sprintf(conv, "public static void main(String[] args) { \n");

	} else {
		sprintf(conv, "public static %s %s() { \n",ret,name);

	}

	struct Node* aux[MAX_STACK_LENGTH];
	int p =0;

	while( current_pos != 0){
		struct Node* node_pop = popNode();
		aux[p] = node_pop;
		p++;
	}
	p--;

	int i;
		for(i = p ; i >= 0 ; i--){
		sprintf(conv,"%s %s",conv, aux[i]->j_conversion);
		}

	sprintf(conv,"%s %s\n",conv,"}");
	n->j_conversion = conv;

	clear_variables();

	return n;
}

//NEW VAR INT
struct Node* create_node_variable(char* name){

	struct Node* n = malloc(sizeof(struct Node));
	add_var(name);
	n->type = v_int;
	struct Node* node_pop = popNode();

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv, "Integer %s = %s; \n", name, node_pop->j_conversion);
	n->j_conversion = conv;

	addNode(n);
	return n;
}

//NEW VAR STRING
struct Node* create_node_string_var(char* name, char* value){

	struct Node* n = malloc(sizeof(struct Node));
	add_var(name);
	n->type = v_string;
	value++;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv, "String %s = \"%s\";\n", name, value);
	n->j_conversion = conv;

	addNode(n);
	return n;
}

struct Node* create_node_if(){
	
	struct Node* n = malloc(sizeof(struct Node));
	n->type = if_node;
	configure_loop_node(n, "if", compare);

	addNode(n);
	return n;
}



struct Node* create_node_for(){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = for_node;
	configure_loop_node(n, "for", from_to);

	addNode(n);
	return n;
}


//WHILE 
struct Node* create_node_while(){

	struct Node* n = malloc(sizeof(struct Node));

	n->type = while_node;
	configure_loop_node(n, "while", compare);

	addNode(n);
	return n;

}


void configure_loop_node(struct Node* n, char* str, types type){

	int condition_while = 0;
	struct Node* aux[MAX_STACK_LENGTH];
	int p = 0;
	struct Node* node_pop = popNode();

	while(condition_while == 0){
			
		if(node_pop->type == type){
			condition_while = 1;
		}
		else{
			aux[p] = node_pop;
			p++;
			node_pop = popNode();
		}
	}
	p--;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%s ( %s ) { \n",str, node_pop->j_conversion);

	int i;
	for(i = p ; i >= 0 ; i--){
		sprintf(conv,"%s %s",conv, aux[i]->j_conversion);
	}

	sprintf(conv,"%s %s\n",conv,"}");
	n->j_conversion = conv;	
}


//READ
struct Node* create_node_read(char* str){

	struct Node* n = malloc(sizeof(struct Node));
	n->type = read_node;
	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH); 

	sprintf(conv, "Scanner _v_%s_s_ = new Scanner(System.in); \n String _v_%s_s_aux_ = _v_%s_s_.next(); \n try { %s = Integer.parseInt(_v_%s_s_aux_); } \n catch (Exception e) { System.out.println(\"skl error: non numeric input\"); System.exit(0); }\n", 
		str, str, str, str, str);
	
	n->j_conversion = conv;

	addNode(n);
	return n;
}

//PRINT
struct Node* create_node_print_string(char* str){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = show_node;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);

	if (str[0] == '.'){
		str++;
		sprintf(conv,"System.out.print(\"%s\\n\");\n", str);
	} else {
		sprintf(conv,"System.out.print(%s); \n System.out.print(\"\\n\"); \n", str);
	}

	n->j_conversion = conv;	

	addNode(n);
	return n;
}

struct Node* create_node_int_print(int num){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = show_node;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"System.out.print(\"%d\\n\"); \n", num);
	n->j_conversion = conv;	

	addNode(n);
	return n;
}


//SET VARIABLES
struct Node* create_node_set_int(char* str){
	
	struct Node* n = malloc(sizeof(struct Node));
	n->type = set_node;
	struct Node* node_pop = popNode();

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%s = %s;\n",str,node_pop->j_conversion);
	n->j_conversion = conv;	

	addNode(n);
	return n;
}

struct Node* create_node_set_string(char* str, char* val){
	
	struct Node* n = malloc(sizeof(struct Node));
	n->type = set_node;
	val++;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%s = \"%s\";\n",str,val);
	n->j_conversion = conv;	

	addNode(n);
	return n;
}


//callfunction node
struct Node* create_node_function_call(char* name){
	
	struct Node* n = malloc (sizeof(struct Node));
	n->type = call_function;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%s();\n",name);
	n->j_conversion = conv;	

	addNode(n);
	return n;
}

//integer node
struct Node* create_node_int_var(char* name, int value){

	struct Node* n = malloc(sizeof(struct Node));
	if (!add_var(name)){
		return NULL;
	}

	
	n->type = v_int;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv, "Integer %s = %d; \n", name, value);
	n->j_conversion = conv;

	addNode(n);
	return n;
}

static struct Node* string_node_to_stack(char* str){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = string_node;
	n->j_conversion = str;

	return n;
}


struct Node* create_node_new_var(char* str){
	struct Node* n = string_node_to_stack(str);
	n->type = v_var;
	return n;
}


//FROM TO 
struct Node* create_node_from_to(char* name, int from, int to){

	struct Node* n = malloc(sizeof(struct Node));

	n->type=from_to;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);

	if (add_var(name)){
		sprintf(conv,"int %s = %d ; %s <= %d ; %s++",name,from,name,to,name);
	}else{
		sprintf(conv,"%s = %d ; %s <= %d ; %s++",name,from,name,to,name);
	}
	n->j_conversion = conv;

	addNode(n);
	return n;

}

struct Node* create_node_from_tochar(char* name, int from, char* to){

	struct Node* n = malloc(sizeof(struct Node));
	n->type=from_to;
	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);

	if (add_var(name)){
		sprintf(conv,"int %s = %d ; %s <= %s ; %s++",name,from,name,to,name);
	}else{
		sprintf(conv,"%s = %d ; %s <= %s ; %s++",name,from,name,to,name);
	}

	n->j_conversion = conv;

	addNode(n);
	return n;

}

struct Node* create_node_fromchar_tochar(char* name, char* from, char* to){

	struct Node* n = malloc(sizeof(struct Node));
	n->type=from_to;
	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);

	if (add_var(name)){
		sprintf(conv,"int %s = %s ; %s <= %s ; %s++",name,from,name,to,name);
	}else{
		sprintf(conv,"%s = %s ; %s <= %s ; %s++",name,from,name,to,name);
	}

	n->j_conversion = conv;

	addNode(n);
	return n;

}


//BOOLEANS
struct Node* create_node_cmp_symbol(char* sym){

	struct Node* n = malloc(sizeof(struct Node));
	n->type = compare;
	struct Node* node_pop = popNode();

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%s ( %s )",sym, node_pop->j_conversion);
	n->j_conversion = conv;	

	addNode(n);
	return n;
}

struct Node* create_node_cmp_symbol_aux(char* sym){
	
	struct Node* n = malloc(sizeof(struct Node));
	n->type = compare;
	struct Node* node_pop1 = popNode();
	struct Node* node_pop2 = popNode();

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%s %s %s\n",node_pop2->j_conversion, sym, node_pop1->j_conversion);
	n->j_conversion = conv;	

	addNode(n);
	return n;

}


//INTOPS

struct Node* create_node_op(char* sym){
	
	struct Node* n = malloc (sizeof(struct Node));
	n->type = op_int;
	struct Node* node_pop1 = popNode();
	struct Node* node_pop2 = popNode();

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%s %s %s",node_pop2->j_conversion, sym, node_pop1->j_conversion);
	n->j_conversion = conv;	

	addNode(n);
	return n;
}


struct Node* create_node_parenthesis(){
	
	struct Node* n = malloc (sizeof(struct Node));
	n->type = op_int;
	struct Node* node_pop = popNode();

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"(%s)",node_pop->j_conversion);
	n->j_conversion = conv;	

	addNode(n);
	return n;

}


///crea un nodo integer simple

struct Node* create_node_int_stack(int value){
	
	struct Node* n = malloc(sizeof(struct Node));
	n->type = int_node;
	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%d",value);
	n->j_conversion = conv;

	return n;

}

//TYPE

struct Node* create_node_integer(int value){
	struct Node* n = create_node_int_stack(value);
	addNode(n);
	return n;
}

struct Node* create_node_call_var(char* sym){
	struct Node* n = malloc (sizeof(struct Node));

	n->type = v_int;

	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv,"%s",sym);
	n->j_conversion = conv;	

	addNode(n);
	return n;
}


//cmp node
struct Node* create_node_cmp(char* sym, struct Node* left, struct Node* right){
	
	struct Node* n = malloc(sizeof(struct Node));
	n->type = compare;
	char* conv = malloc(sizeof(char) * MAX_J_CONV_LENGTH);
	sprintf(conv, "%s %s %s", left->j_conversion, sym, right->j_conversion);
	n->j_conversion = conv;

	addNode(n);

	return n;
}
