#ifndef BANANA_SRC_LEXER_TOKEN_H
#define BANANA_SRC_LEXER_TOKEN_H


typedef enum {
    TypeNormal,
    TypeNumber,
    TypeSpace,
    TypeSymbol,
    TypeEnd,
    //  ===  算術演算子 ===
    TypeOpAdd,
    TypeOpSub,
    TypeOpMul,
    TypeOpDiv,

    TypeOpAssign,

    TypeRparen,
    TypeLparen,

    TypeFuncSym,
} TokenType;

typedef struct {
    char *token;
    TokenType type;
} Token;


#include "../banana.h"


TokenType change_op_symbol(char *value);


TokenType sorting_normal_token(char *token_text);


void free_all_token_ptr(Token *token_list_ptr);
Token* make_token_list_ptr(char *buffer);

#endif