#ifndef BANANA_SRC_VARIABLE_VARIABLE_H
#define BANANA_SRC_VARIABLE_VARIABLE_H


#include "../banana.h"


typedef struct {
    char *var_name;
    CalculNode *value;
} VariableNode;


VariableNode* make_variable_node(Token *token_list_ptr, int *pos);


#endif