#ifndef BANANA_SRC_PARSE_PARSE_H
#define BANANA_SRC_PARSE_PARSE_H


#include "../banana.h"


typedef enum {
    Add,
    Sub,
    Mul,
    Div,

    Num,
} OpType;

typedef struct CalculNode {
    char *value;
    OpType type;
    struct CalculNode *left;
    struct CalculNode *right;
} CalculNode;


CalculNode *parse_expr(Token *token_list_ptr, int *pos);
int calcul_eval(CalculNode* n);
void free_all_calcul_node(CalculNode *n);


void make_process_data(Token *token_list_ptr);


#endif