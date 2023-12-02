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
    NodeType_Positive,
    NodeType_Negative,
};

typedef int Precedence;
enum {
    Precedence_MIN,
    Precedence_Term,
    Precedence_Factor,
    Precedence_Power,
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

typedef struct Parser {
    Lexer lexer;
    Token curr;
} Parser;


Node *Alloc_Node();
void Dealloc_Tree(Node *tree);
void PrintNode (Node *tree);
void PrintTree(Node *tree);

void parser_init(Parser *parser, string expression);
Node *parser_parse_expression(Parser *parser, Precedence prev_operator_prec);

#endif
