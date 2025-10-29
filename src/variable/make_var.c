#include "variable.h"


VariableNode* make_variable_node(Token *token_list_ptr, int *pos) {
    VariableNode *var_node = (VariableNode *)malloc(sizeof(VariableNode));
    int assigned_value = 0;
    int defined_var_name = 0;

    while (token_list_ptr[*pos].type != TypeEnd) {
        if (token_list_ptr[*pos].type == TypeOpAssign) {
            assigned_value = 1;
        } else if (token_list_ptr[*pos].type == TypeSpace) {
            (*pos)++;
            continue;
        } else {
            if (token_list_ptr[*pos].type == TypeNormal) {
                if (defined_var_name) {
                    var_node->value = parse_expr(token_list_ptr, pos);
                    break;
                }
                defined_var_name = 1;
                var_node->var_name = (char *)malloc((int)strlen(token_list_ptr[*pos].token));
                strcpy(var_node->var_name, token_list_ptr[*pos].token);
            } else if (defined_var_name) {
                var_node->value = parse_expr(token_list_ptr, pos);
                break;
            }
        }

        (*pos)++;
    }

    add_variable(var_node);
    return var_node;
}