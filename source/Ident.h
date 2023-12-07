#ifndef IDENT
#define IDENT

typedef struct Identifier {
    char letter;
    float value;
    struct Identifier *next;
} Identifier;


void ident_init(Identifier *ident);
Identifier *ident_add(Identifier *ident, char letter, float value);
Identifier *ident_new(char letter, float value);
Identifier *ident_find(Identifier *ident ,char letter);

#endif
