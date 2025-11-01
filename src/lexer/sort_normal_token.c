#include "token.h"


TokenType sorting_normal_token(char *token_text) {
    if (!strcmp(token_text, "def")) {
        return TypeFuncSym;
    }

    return TypeNormal;
}