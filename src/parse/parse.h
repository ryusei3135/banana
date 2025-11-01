#ifndef BANANA_SRC_PARSE_PARSE_H
#define BANANA_SRC_PARSE_PARSE_H


#include "../banana.h"


typedef enum {
    Add,
    Sub,
    Mul,
    Div,

    Num,
    //  ===  関係演算子 ===
    TypeOpEpual,
    TypeOpBigger,
    TypeOpSmallerThen,
    TypeOpHigher,
    TypeOpBelow,
    TypeOpIsNot,
    //  === 論理演算子 ===
    TypeOpAnd,
    TypeOpOr,
} OpType;

typedef struct CalculNode {
    char *value;
    OpType type;
    struct CalculNode *left;
    struct CalculNode *right;
} CalculNode;

typedef struct {
    struct CalculNode **data;
} ParenExpr;

typedef struct VariableNode {
    char *var_name;
    struct CalculNode *value;
} VariableNode;


//  === calcul.c ===
CalculNode *parse_expr(Token *token_list_ptr, int *pos);
int calcul_eval(CalculNode* n);
void free_all_calcul_node(CalculNode *n);

//  === parse.c ===
OpType soring_operator_token_type(char *token_text);
void make_process_data(Token *token_list_ptr);

//  === paren_expr.c ===
ParenExpr* make_paren_expr_data(Token *token_list_ptr, int *pos);
void free_expr_memory(ParenExpr *expr_ptr);


#endif