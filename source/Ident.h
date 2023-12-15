#ifndef IDENT
#define IDENT

#include "Parser.h"

typedef struct Identifier {
    char letter;
    float value;
    struct Identifier *next;
} Identifier;

typedef struct Function {
    char letter;
    char *args;
    Node *expr;
    struct Function *next;
} Function;

void func_init(Function *func);
Function *func_find(Function *func, char letter);
Function *func_add(Function *func, char letter, char args[], Node *expr);

void ident_init(Identifier *ident);
Identifier *ident_add(Identifier *ident, char letter, float value);
Identifier *ident_find(Identifier *ident ,char letter);

#endif
