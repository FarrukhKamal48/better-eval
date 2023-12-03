#include <string.h>
#include <stdlib.h>

#include "clib.h"

unsigned short int isDigit(char a) {
    switch (a) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return 1;

        default: return 0;
    }
}

unsigned short int isWhitspace(char a) {
    switch (a) {
        case ' ': case '\r': case '\t': case '\n': return 1; 

        default: return 0;
    }
}; 

string strMake(char expr[]) {
    return (string) {
        .str = expr,
        .size = strlen(expr)
    };
};

float lexeme_to_number (string lexeme) {
    return strtod(lexeme.str, NULL);
};

Node *Alloc_Node() {
    Node *newNode = malloc(sizeof(Node));
    while (newNode == NULL) {
        Node *newNode = malloc(sizeof(Node));
    }
    return newNode;
}

void Dealloc_Tree(Node *tree) {
    if (tree->type == NodeType_Num) { 
        free(tree); 
        return;
    }
    
    Dealloc_Tree(tree->binary.left);
    Dealloc_Tree(tree->binary.right);
    free(tree);
};
