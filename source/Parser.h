#ifndef PARSER
#define PARSER

#include "Lexer.h"

typedef int NodeType;
enum {
    NodeType_Pow,
    NodeType_Div,
    NodeType_Mul,
    NodeType_Add,
    NodeType_Sub,

    NodeType_Num,
};

typedef struct Node Node ;
struct Node {
    NodeType type;

    union {
        float number;
        struct {Node *operand;} unary;
        struct {Node *left; Node *right;} binary;
    };
};

void Dealloc_Tree(Node *tree);

void PrintNode (Node *tree);
void PrintTree(Node *tree);

#endif
