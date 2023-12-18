#include <stdlib.h>
#include <stdio.h>
#include "Ident.h"
#include "../lib/debug.h"
#include "../lib/clib.h"

void printFunc(Function **func) {
    Function *curr = *func;
    if (curr == NULL)   printf("\nFunctions not declared\n");
    else                printf("\nFUNCTIONS: \n");
    while (curr != NULL) {
        printf("%s%c(%c):\n", colors[5], curr->letter, curr->arg);
        parser_print_tree(curr->expr, 2);
        curr = curr->next;
    }
}
void func_init(Function *func) {
    func->letter = '\0';
    func->next = NULL;
}
Function *func_find(Function *func, char letter) {
    Function *ret = func;
    while (ret != NULL) {
        if (ret->letter == letter)
            return ret;
        ret = ret->next;
    }
    return NULL;
}
Function *func_new(char letter, char arg, Node *expr) {
    Function *ret = malloc(sizeof(Function));
    ret->letter = letter;
    ret->arg = arg;
    ret->expr = expr;
    ret->next = NULL;
    return ret;
}
Function *func_add(Function **func, char letter, char arg, Node *expr) {
    Function *new = NULL;
    if (*func == NULL) {
        new = func_new(letter, arg, expr);
        *func = new;
    }
    else {
        new = func_new(letter, arg, expr);
        new->next = *func;
        *func = new;
    }
    return new;
}


void printIdent(Identifier **ident) {
    Identifier *curr = *ident;
    if (curr == NULL)   printf("\nVaraibles not set\n");
    else                printf("\nVARIABLES: \n");
    while (curr != NULL) {
        printf("%c = %f\n", curr->letter, curr->value);
        curr = curr->next;
    }
}
Identifier *ident_find(Identifier *ident, char letter) {
    Identifier *ret = ident;
    while (ret != NULL) {
        if (ret->letter == letter)
            return ret;
        ret = ret->next;
    }
    return NULL;
}

Identifier *ident_new(char letter, float value) {
    Identifier *ret = malloc(sizeof(Identifier));
    ret->letter = letter;
    ret->value = value;
    ret->next = NULL;
    return ret;
}

Identifier *ident_add(Identifier **ident, char letter, float value) {
    Identifier *new = NULL;
    if (*ident == NULL) {
        new = ident_new(letter, value);
        *ident = new;
    }
    else {
        new = ident_new(letter, value);
        new->next = *ident;
        *ident = new;
    }
    return new;
}

