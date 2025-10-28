#include "parse.h"


void make_process_data(Token *token_list_ptr) {
    int pos = 0;
    while (token_list_ptr[pos].type != TypeEnd) {
        if (token_list_ptr[pos].type == TypeNumber) {
            CalculNode *node = parse_expr(token_list_ptr, &pos);
            printf("%d value\n", calcul_eval(node));
        }
    }
}