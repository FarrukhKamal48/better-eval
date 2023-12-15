#include <stdlib.h>
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
Function *func_new(char letter, char args[], Node *expr) {
    Function *ret = malloc(sizeof(Function));
    ret->letter = letter;
    ret->args = args;
    ret->expr = expr;
    ret->next = NULL;
    return ret;
}
Function *func_add(Function *func, char letter, char args[], Node *expr) {
    if (func->letter == '\0') {
        func = func_new(letter, args, expr);
        return func;
    }
    Function *new_func = func_new(letter, args, expr); 
    new_func->next = func;
    func = new_func;
    
    return new_func;
}


void ident_init(Identifier *ident) {
    ident->letter = '\0';
    ident->next = NULL;
}
Identifier *ident_new(char letter, float value) {
    Identifier *ret = malloc(sizeof(Identifier));
    ret->letter = letter;
    ret->value = value;
    ret->next = NULL;
    return ret;
}
Identifier *ident_find(Identifier *ident, char letter) {
    Identifier *ret;
    while (ident != NULL) {
        if (ident->letter == letter || ident->letter == '\0') {
            ret = ident;
            ret->letter = letter;
            return ret;
        }
        ident = ident->next;
    }
    return NULL;
}
Identifier *ident_add(Identifier *ident, char letter, float value) {
    if (ident->letter == '\0') {
        ident = ident_new(letter, value);
        return ident;
    }
    Identifier *new_ident = ident_new(letter, value);
    new_ident->next = ident;
    ident = new_ident;
    
    return ident;
}
