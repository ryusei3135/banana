#ifndef BANANA_SRC_VARIABLE_VARIABLE_H
#define BANANA_SRC_VARIABLE_VARIABLE_H

#include "../banana.h"
#include "../parse/parse.h"


typedef struct VariableNode VariableNode;

VariableNode* make_variable_node(Token *token_list_ptr, int *pos);


int add_variable(VariableNode *var_data);
struct CalculNode* get_var_value(char *var_name);


#endif