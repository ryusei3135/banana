#include "parse.h"


ParenExpr* make_paren_expr_data(Token *token_list_ptr, int *pos) {
    ParenExpr *expr = (ParenExpr *)malloc(sizeof(ParenExpr));
    int expr_range = 2;
    int palen_start = 0;

    if (token_list_ptr[*pos].type == TypeLparen) {
        palen_start = 1;
        (*pos)++;
    }

    while (token_list_ptr[*pos].type != TypeEnd) {
        if (token_list_ptr[*pos].type != TypeSpace) {
            expr->data[palen_start - 1] = parse_expr(token_list_ptr, pos);
            palen_start ++;
            if (palen_start >= 2) {
                expr->data[palen_start - 1] = (CalculNode *)realloc(
                        expr->data, 
                        sizeof(CalculNode) 
                        * palen_start);
            }
        }
        if (token_list_ptr[*pos].type == TypeRparen) {
            palen_start = 0;
            break;
        }
    }

    if (!palen_start) {
        free_expr_memory(expr);
        //   err
        exit(1);
    } else {
        return expr;
    }
}

void free_expr_memory(ParenExpr *expr_ptr) {
    for (int count = 0; &expr_ptr[count]; count++) {
        free_all_calcul_node(expr_ptr->data[count]);
    }
    free(expr_ptr);
}