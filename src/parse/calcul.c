#include "parse.h"


static CalculNode *make_num_node(char *value, int *pos) {
    CalculNode *node = (CalculNode *)malloc(sizeof(CalculNode));

    //  ノードに値を代入し初期化
    node->value = (char *)malloc(strlen(value));
    strcpy(node->value, value);
    node->left = NULL;
    node->right = NULL;

    //  ノードのタイプを代入
    node->type = Num;

    (*pos)++;
    return node;
}

static CalculNode *make_op_node(OpType type, CalculNode *left, CalculNode *right) {
    CalculNode *node = (CalculNode *)malloc(sizeof(CalculNode));
    node->value = NULL;
    node->left = left;
    node->right = right;
    node->type = type;
    return node;
}

static CalculNode *parse_factor(Token *token_list_ptr, int *pos) {
    if (token_list_ptr[*pos].type == TypeNumber) {
        return make_num_node(token_list_ptr[*pos].token, pos);
    } else if (token_list_ptr[*pos].type == TypeNormal) {
        //
        CalculNode *node = get_var_value(token_list_ptr[*pos].token);
        (*pos)++;
        return node;
    }

    if (token_list_ptr[*pos].type == TypeLparen) {
        (*pos)++;
        CalculNode *node = parse_expr(token_list_ptr, pos);

        //  エラー
        if (token_list_ptr[*pos].type != TypeRparen) {
            // print_error(ERR_0x01_SYNTAX_ERR, token_list_ptr[*pos].buffer);
            exit(1);
        }

        (*pos)++;
        return node;
    }

    if (token_list_ptr[*pos].type == TypeSpace) {
        (*pos)++;
        return parse_factor(token_list_ptr, pos);
    }

    exit(1);
}

static CalculNode *parse_term(Token *token_list_ptr, int *pos) {
    CalculNode *node = parse_factor(token_list_ptr, pos);

    while (token_list_ptr[*pos].type != TypeEnd) {
        if (token_list_ptr[*pos].type == TypeOpMul) {
            (*pos)++;
            node = make_op_node(Mul, node, parse_factor(token_list_ptr, pos));
        } else if (token_list_ptr[*pos].type == TypeOpDiv) {
            (*pos)++;
            node = make_op_node(Div, node, parse_factor(token_list_ptr, pos));
        } else if (token_list_ptr[*pos].type == TypeSpace) {
            (*pos)++;
        } else {
            break;
        }
    }

    return node;
}

CalculNode *parse_expr(Token *token_list_ptr, int *pos) {
    CalculNode *node = parse_term(token_list_ptr, pos);

    while (token_list_ptr[*pos].type != TypeEnd) {
        if (token_list_ptr[*pos].type == TypeOpAdd) {
            (*pos)++;
            node = make_op_node(Add, node, parse_term(token_list_ptr, pos));
        } else if (token_list_ptr[*pos].type == TypeOpSub) {
            (*pos)++;
            node = make_op_node(Sub, node, parse_term(token_list_ptr, pos));
        } else if (token_list_ptr[*pos].type == TypeSpace) {
            (*pos)++;
        } else {
            break;
        }
    }

    return node;
}


int calcul_eval(CalculNode* n) {
    switch (n->type) {
        case Num: return atoi(n->value);
        case Add: return calcul_eval(n->left) + calcul_eval(n->right);
        case Sub: return calcul_eval(n->left) - calcul_eval(n->right);
        case Mul: return calcul_eval(n->left) * calcul_eval(n->right);
        case Div: return calcul_eval(n->left) / calcul_eval(n->right);
    }
    return 0;
}

void free_all_calcul_node(CalculNode *n) {
    if (n->value) {
        free(n->value);
    }
    if (n->left) {
        free_all_calcul_node(n->left);
        free(n->left);
    } else if (n->right) {
        free_all_calcul_node(n->right);
        free(n->right);
    }
}