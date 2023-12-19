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
    char arg;
    Node *expr;
    Node *argxpr;
    struct Function *next;
} Function;

void printFunc(Function **func);
Function *func_add(Function **func, char letter, char arg, Node *expr);
Function *func_find(Function *func, char letter);

void printIdent(Identifier **ident);
Identifier *ident_add(Identifier **ident, char letter, float value);
Identifier *ident_find(Identifier *ident , char letter);

#endif
