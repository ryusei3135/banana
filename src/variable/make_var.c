#include "variable.h"


VariableNode* make_variable_node(Token *token_list_ptr, int *pos) {
    VariableNode *node = (VariableNode *)malloc(sizeof(VariableNode));
    int assigned_var_name = 0;
    int assigned_value = 0;
    int bool_variable_data = 0;

    while (token_list_ptr[*pos].type != TypeEnd) {
        if (token_list_ptr[*pos].type == TypeNormal) {
            if (assigned_var_name) { //  err
                break;
            }
            node->var_name = (char *)malloc((int)strlen(token_list_ptr[*pos].token));
            strcpy(node->var_name, token_list_ptr[*pos].token);
            assigned_var_name = 1;
        }

        if (assigned_var_name && token_list_ptr[*pos].type == TypeOpAssign) {
            if (assigned_value) { //  err
                break;
            }
            assigned_value = 1;
        }

        if (token_list_ptr[*pos].type == TypeSpace) {
            (*pos)++;
            continue;
        } else if (assigned_value) {
            node->value = parse_expr(token_list_ptr, pos);
            bool_variable_data = 1;
            break;
        }
    }

    if (bool_variable_data) {
        return node;
    } else { //  err
        return NULL;
    }
}