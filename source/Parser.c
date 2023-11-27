#include "Parser.h"
#include "Lexer.h"
#include <stdlib.h>

static Precedence Precedence_Lookup[5] = {
    [TokenType_Plus]  = Precedence_Term,
    [TokenType_Minus] = Precedence_Term,
    [TokenType_Star]  = Precedence_Factor,
    [TokenType_Slash] = Precedence_Factor,
    [TokenType_Caret] = Precedence_Power,
};

void parser_init(Parser *parser, string expresssion) {
    parser->curr = (Token) {0};
    lexer_init(&parser->lexer, expresssion);
};

void parser_advance(Parser *parser) {
    parser->curr = lexer_next_token(&parser->lexer);
}

Node *parser_parse_number(Parser *parser) {
    Node *ret = malloc(sizeof(Node));
    ret->type = NodeType_Number;
    ret->number = lexeme_to_number(parser->curr.lexeme);
    parser_advance(parser);
    return ret;
}

Node *parser_parse_terminal_expr(Parser *parser) {
    Node *ret;
    if (parser->curr.type == TokenType_Num) {
        return parser_parse_number(parser);
    }
    else if (parser->curr.type == TokenType_OpenParen) {
        parser_advance(parser);
        ret = parser_parse_expression(parser, Precedence_Min);
        if (parser->curr.type == TokenType_CloseParen) {
            parser_advance(parser);
        }
    }
    else if (parser->curr.type == TokenType_Plus) {
        parser_advance(parser);
        ret = malloc(sizeof(Node));
        ret->type = NodeType_Positive;
        ret->unaray.operand = parser_parse_number(parser);
    }
    else if (parser->curr.type == TokenType_Minus) {
        parser_advance(parser);
        ret = malloc(sizeof(Node));
        ret->type = NodeType_Negative;
        ret->unaray.operand = parser_parse_number(parser);
    }
    return ret;
}

Node *parser_build_right_node(Parser *parser, Token operater, Node *left) {
    Node *ret = malloc(sizeof(Node));
    switch (operater.type) {
        case TokenType_Caret: ret->type = NodeType_Pow;
        case TokenType_Slash: ret->type = NodeType_Div;
        case TokenType_Star: ret->type = NodeType_Mul;
        case TokenType_Plus: ret->type = NodeType_Add;
        case TokenType_Minus: ret->type = NodeType_Sub;
    }
    ret->binary.left = left;
    ret->binary.right = parser_parse_expression(parser, Precedence_Lookup[operater.type]);
    return ret;
}

Node *parser_parse_expression(Parser *parser, Precedence prev_prec) {
    Node *left = parser_parse_number(parser);
    Token curr_operator = parser->curr;
    Precedence curr_prec = Precedence_Lookup[curr_operator.type];
    while (curr_prec != Precedence_Min) {
        if (prev_prec >= curr_prec) {
            break;
        }
        else {
            parser_advance(parser);
            left = parser_build_right_node(parser, curr_operator, left);
            curr_operator = parser->curr;
            curr_prec = Precedence_Lookup[curr_operator.type];
        }
    }
    return left;
}
