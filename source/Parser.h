#ifndef PARSER
#define PARSER

#include "Lexer.h"

typedef int NodeType;
enum {
    NodeType_Number,
    NodeType_Pow,
    NodeType_Div,
    NodeType_Mul,
    NodeType_Add,
    NodeType_Sub,

    NodeType_Error,
};

typedef int Precedence;
enum {
    Precedence_Min,
    Precedence_Term,
    Precedence_Factor,
    Precedence_Power,
};

// static Precedence Precedence_Lookup[5] = {
//     [TokenType_Plus]  = Precedence_Term,
//     [TokenType_Minus] = Precedence_Term,
//     [TokenType_Star]  = Precedence_Factor,
//     [TokenType_Slash] = Precedence_Factor,
//     [TokenType_Caret] = Precedence_Power,
// };

typedef struct Node Node;
struct Node {
    NodeType type;
    union {
        float number;
        struct { Node *operand; } unaray;
        struct { Node *left; Node *right; } binary;
    };
};

typedef struct Parser {
    Lexer lexer;
    Token curr;
} Parser;


void parser_init(Parser *parser, string expresssion);

void parser_advance(Parser *parser);

Node *parser_parse_number(Parser *parser);

Node *parser_build_right_node(Parser *parser, Token operater, Node *left);

Node *parser_parse_expression(Parser *parser, Precedence prev_prec);

#endif
