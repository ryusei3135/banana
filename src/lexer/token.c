#include "token.h"


static TokenType change_op_symbol(char *value) {
    if (!strcmp(value, "+")) {
        return TypeOpAdd;
    } else if (!strcmp(value, "-")) {
        return TypeOpSub;
    } else if (!strcmp(value, "*")) {
        return TypeOpMul;
    } else if (!strcmp(value, "/")) {
        return TypeOpDiv;
    } else if (!strcmp(value, "=")) {
        return TypeOpAssign;
    }

    return TypeSymbol;
}

static int _is_normal(char chr) {
    if (isalpha(chr) || chr == '_') {
        return 1;
    }
    return 0;
}

static int _is_number(char chr) {
    if (isdigit(chr)) {
        return 1;
    }
    return 0;
}

static int _is_space(char chr) {
    if (isspace(chr) && chr != '\0') {
        return 1;
    }
    return 0;
}

static int _is_symbol(char chr) {
    if (ispunct(chr)) {
        return 1;
    }
    return 0;
}

static TokenType is_token_type(char chr) {
    if (_is_normal(chr)) {
        return TypeNormal;
    } else if (_is_number(chr)) {
        return TypeNumber;
    } else if (_is_space(chr)) {
        return TypeSpace;
    } else if (_is_symbol(chr)) {
        return TypeSymbol;
    }

    return TypeEnd;
}

static int is_token(char chr, TokenType type) {
    int result = 0;
    switch (type) {
        case TypeNormal:
            result = _is_normal(chr);
            break;
        case TypeNumber:
            result = _is_number(chr);
            break;
        case TypeSpace:
            result = _is_space(chr);
            break;
        case TypeSymbol:
            result = _is_symbol(chr);
            break;
        default:
            break;
    }
    return result;
}


static Token token_end_ptr() {
    char *end_text = (char *)malloc(5);
    strcpy(end_text, "_end");
    return (Token){end_text, TypeEnd};
}

static void assign_token_list_ptr(Token **token_list_ptr, Token assign_token, int *token_ptr_memory_count) {
    if (*token_ptr_memory_count > 1) {
        (*token_list_ptr) = (Token *)realloc(
                (*token_list_ptr), 
                sizeof(Token) 
                    * (*token_ptr_memory_count));
    }
    (*token_list_ptr)[*token_ptr_memory_count - 1] = assign_token;
    (*token_ptr_memory_count)++;
}

static Token cut_token_text(char **buffer, TokenType type) {
    int token_length = 0;

    while (is_token(*((*buffer) + token_length), type)) token_length++;

    char *token_text = (char *)malloc(token_length);
    strncpy(token_text, (*buffer), token_length);
    token_text[token_length] = '\0';
    *buffer += token_length;

    if (type == TypeSymbol) {
        type = change_op_symbol(token_text);
    }

    return (Token){token_text, type};
}

void free_all_token_ptr(Token *token_list_ptr) {
    int count = 0;
    while (token_list_ptr[count].type != TypeEnd) {
        free(token_list_ptr[count].token);
        count++;
    }
    free(token_list_ptr[count].token);
    free(token_list_ptr);
}

Token* make_token_list_ptr(char *buffer) {
    Token *token_list_ptr = (Token *)malloc(sizeof(Token));
    TokenType now_type;
    int token_ptr_memory_count = 1;

    int buffer_length = (int)strlen(buffer);

    while (*buffer != '\0' && *buffer != '\n') {
        if ((now_type = is_token_type(*buffer)) >= 0) {
            assign_token_list_ptr(&token_list_ptr, cut_token_text(&buffer, now_type), &token_ptr_memory_count);
            continue;
        }

        buffer++;
    }
    assign_token_list_ptr(&token_list_ptr, token_end_ptr(), &token_ptr_memory_count);

    return token_list_ptr;
}