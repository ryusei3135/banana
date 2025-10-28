#ifndef BANANA_SRC_LEXER_TOKEN_H
#define BANANA_SRC_LEXER_TOKEN_H


typedef enum {
    TypeNormal,
    TypeNumber,
    TypeSpace,
    TypeSymbol,
    TypeEnd,

    TypeOpAdd,
    TypeOpSub,
    TypeOpMul,
    TypeOpDiv,

    TypeOpAssign,

    TypeRparen,
    TypeLparen,
} TokenType;

typedef struct {
    char *token;
    TokenType type;
} Token;


#include "../banana.h"


void free_all_token_ptr(Token *token_list_ptr);
Token* make_token_list_ptr(char *buffer);

#endif