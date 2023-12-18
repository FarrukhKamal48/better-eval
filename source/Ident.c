#include <stdlib.h>
#include <stdio.h>
#include "Ident.h"

void func_init(Function *func) {
    func->letter = '\0';
    func->next = NULL;
}
Function *func_find(Function *func, char letter) {
    Function *ret;
    while (func != NULL) {
        if (func->letter == letter || func->letter == '\0') {
            ret = func;
            ret->letter = letter;
            return ret;
        }
        func = func->next;
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
Function *func_add(Function *func, char letter, char arg, Node *expr) {
    if (func->letter == '\0') {
        func = func_new(letter, arg, expr);
        return func;
    }
    Function *new_func = func_new(letter, arg, expr); 
    new_func->next = func;
    func = new_func;
    
    return new_func;
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

