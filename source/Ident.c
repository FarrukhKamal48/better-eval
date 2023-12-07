#include <stdlib.h>
#include "Ident.h"

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
    for (; ident != NULL; ident = ident->next) {
        if (ident->letter == letter || ident->letter == '\0') {
            ret = ident;
            ret->letter = letter;
            return ret;
        }
    };
    return NULL;
}

Identifier *ident_add(Identifier *ident, char letter, float value) {
    if (ident->letter == '\0') {
        ident = ident_new(letter, value);
        return ident;
    }
    for (; ident->next != NULL; ident = ident->next);
    ident->next = ident_new(letter, value);
    return ident->next;
}
