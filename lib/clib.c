#include <stdio.h>
#include <stdlib.h>

#include "clib.h"

unsigned short int isDigit(char a) {
    return a >= '0' && a <= '9';
}

unsigned short int isAlpha(char a) {
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
} 

unsigned short int isWhitspace(char a) {
    switch (a) {
        case ' ': case '\r': case '\t': case '\n': return 1; 
        default: return 0;
    }
}; 

int len(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
string strMake(char expr[]) {
    return (string) {
        .str = expr,
        .size = len(expr)
    };
};

float Abs(float val) {
    if (val < 0) return -val;
    return val;
};

int Ceil(float num) {
    int inum = (int)num;
    if (num == (float)inum) {
        return inum;
    }
    return inum + 1;
}

float Fact(float val) {
    if (val<0) return FLOAT_MAX;
    float result; 
    for (result = 1; val > 0; val--) {
        result *= val;
    }
    return (float)result;
}

void Fgets(char *str, int size) {
    fgets(str, size, stdin);
    str[len(str)-1] = '\0';
}

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
    switch (tree->type) {
        case NodeType_Num: case NodeType_ERROR: free(tree); break;

        case NodeType_Positive: case NodeType_Negative: Dealloc_Tree(tree->unary.operand); break;

        case NodeType_Pow: case NodeType_Div: case NodeType_Mul: case NodeType_Add: case NodeType_Sub: {
            Dealloc_Tree(tree->binary.left);
            Dealloc_Tree(tree->binary.right);
        } break;
    }
};
