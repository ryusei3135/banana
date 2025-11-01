#include "token.h"


TokenType change_op_symbol(char *value) {
    //  ===  算術演算子 ===
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