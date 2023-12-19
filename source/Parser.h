#ifndef PARSER
#define PARSER

#include "Lexer.h"

typedef int NodeType;
enum {
    NodeType_Pow,
    NodeType_Div,
    NodeType_Mul,
    NodeType_Mod,
    NodeType_Add,
    NodeType_Sub,
    NodeType_Equal,

    NodeType_Num,
    NodeType_Ident,
    NodeType_Func,
    NodeType_Abs,
    NodeType_Positive,
    NodeType_Negative,
    NodeType_Factorial,

    NodeType_ERROR,
};

typedef int Precedence;
enum {
    Precedence_MIN,
    Precedence_Equality,
    Precedence_Term,
    Precedence_Factor,
    Precedence_Power,
};

typedef struct Node Node ;
struct Node {
    NodeType type;
    char letters[2];

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


void parser_init(Parser *parser, string expression);
Node *parser_parse_expression(Parser *parser, Precedence prev_operator_prec);
void ident_node_replace(Node *expr, char prev_letter, char new_letter, float new_number);
Node *ident_node_find(Node *expr);

#endif
