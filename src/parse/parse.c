#include "parse.h"


OpType soring_operator_token_type(char *token_text) {
    //  === 関係演算子 ===
    if (!strcmp(token_text, "==")) {
        return TypeOpEpual;
    } else if (!strcmp(token_text, ">")) {
        return TypeOpBigger;
    } else if (!strcmp(token_text, "<")) {
        return TypeOpSmallerThen;
    } else if (!strcmp(token_text, ">=")) {
        return TypeOpHigher;
    } else if (!strcmp(token_text, "<=")) {
        return TypeOpBelow;
    } else if (!strcmp(token_text, "!=")) {
        return TypeOpIsNot;
    }
    //   ===  論理演算  ===
    if (!strcmp(token_text, "&&")) {
        return TypeOpAnd;
    } else if (!strcmp(token_text, "||")) {
        return TypeOpOr;
    }

    return -1;
}


void make_process_data(Token *token_list_ptr) {
    int pos = 0;
    while (token_list_ptr[pos].type != TypeEnd) {
        if (token_list_ptr[pos].type == TypeNumber) {
            CalculNode *node = parse_expr(token_list_ptr, &pos);
            printf("%d value\n", calcul_eval(node));
            free_all_calcul_node(node);
        } else if (token_list_ptr[pos].type == TypeNormal) {
            VariableNode *node = make_variable_node(token_list_ptr, &pos);
            printf("%d value\n", calcul_eval(get_var_value(node->var_name)));
        }
    }
}