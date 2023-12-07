#ifndef PARSER
#define PARSER

#include "Lexer.h"
#include "Ident.h"

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
    NodeType_Abs,
    NodeType_Positive,
    NodeType_Negative,

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

#endif
