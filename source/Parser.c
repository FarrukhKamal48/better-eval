#include "../lib/clib.h"
#include <stdio.h>
#include "Parser.h"


static Precedence Precedence_Lookup[TokenType_MAX] = {
    [TokenType_Equal]  = Precedence_Equality,
    [TokenType_Plus]   = Precedence_Term,
    [TokenType_Minus]  = Precedence_Term,
    [TokenType_Slash]  = Precedence_Factor,
    [TokenType_Star]   = Precedence_Factor,
    [TokenType_Modulo] = Precedence_Factor,
    [TokenType_Caret]  = Precedence_Power,
};

void parser_advance(Parser *parser) {
    parser->curr = lexer_next_token(&parser->lexer);
};

void parser_init(Parser *parser, string expression) {
    parser->curr = (Token) {0};
    lexer_init(&parser->lexer, expression);
    parser_advance(parser);
}

Node *parser_parse_number(Parser *parser) {
    Node *ret = Alloc_Node();
    ret->type = NodeType_Num;
    ret->number = lexeme_to_number(parser->curr.lexeme);
    parser_advance(parser);
    return ret;
}

Node *parser_parse_terminal_expr(Parser *parser) {
    Node *ret = 0;
    if (parser->curr.type == TokenType_Num) {
        ret = parser_parse_number(parser);
    }
    else if (parser->curr.type == TokenType_Ident) {
        ret = Alloc_Node();
        ret->type = NodeType_Ident;
        ret->number = *parser->curr.lexeme.str;
        parser_advance(parser);
    }
    else if (parser->curr.type == TokenType_OpenParen) {
        parser_advance(parser);
        ret = parser_parse_expression(parser, Precedence_MIN);
        if (parser->curr.type == TokenType_CloseParen) {
            parser_advance(parser);
        }
    }
    else if (parser->curr.type == TokenType_OpenPipe) {
        parser_advance(parser);
        ret = Alloc_Node();
        ret->type = NodeType_Abs;
        ret->unary.operand = parser_parse_expression(parser, Precedence_MIN);
        if (parser->curr.type == TokenType_ClosePipe) {
            parser_advance(parser);
        }
    }
    else if (parser->curr.type == TokenType_Plus) {
        parser_advance(parser);
        ret = Alloc_Node();
        ret->type = NodeType_Positive;
        ret->unary.operand = parser_parse_terminal_expr(parser);
    }
    else if (parser->curr.type == TokenType_Minus) {
        parser_advance(parser);
        ret = Alloc_Node();
        ret->type = NodeType_Negative;
        ret->unary.operand = parser_parse_terminal_expr(parser);
    }
    else if (!ret) {
        ret = Alloc_Node();
        ret->type = NodeType_ERROR;
    }

    Node *fact_ret = 0;
    if (parser->curr.type == TokenType_Exclaim) {
        fact_ret = Alloc_Node();
        fact_ret->type = NodeType_Factorial;
        fact_ret->unary.operand = ret;
    }
    
    Node *mult_ret = 0;
    if (parser->curr.type == TokenType_Num || parser->curr.type == TokenType_OpenParen 
        || parser->curr.type == TokenType_OpenPipe) {
        mult_ret = Alloc_Node();
        mult_ret->type = NodeType_Mul;
        if (fact_ret)  mult_ret->binary.left = fact_ret; 
        else           mult_ret->binary.left = ret; 
        mult_ret->binary.right = parser_parse_expression(parser, Precedence_Lookup[Precedence_Factor]);
    }
    
    if (mult_ret != 0)      return mult_ret;
    else if (fact_ret != 0) return fact_ret;
    return ret;
}

Node *parser_parse_inifix_expr(Parser *parser, Token operator, Node *left) {
    Node *ret = Alloc_Node();
    switch (operator.type) {
        case TokenType_Caret:  ret->type = NodeType_Pow; break;
        case TokenType_Slash:  ret->type = NodeType_Div; break;
        case TokenType_Star:   ret->type = NodeType_Mul; break;
        case TokenType_Modulo: ret->type = NodeType_Mod; break;
        case TokenType_Plus:   ret->type = NodeType_Add; break;
        case TokenType_Minus:  ret->type = NodeType_Sub; break;
        case TokenType_Equal:  ret->type = NodeType_Equal; break;
    }
    ret->binary.left = left;
    ret->binary.right = parser_parse_expression(parser, Precedence_Lookup[operator.type]);
    return ret;
}

Node *parser_parse_expression(Parser *parser, Precedence prev_operator_prec) {
    Node *left = parser_parse_terminal_expr(parser);
    Token curr_operator = parser->curr;
    Precedence cur_operator_prec = Precedence_Lookup[curr_operator.type];

    while (cur_operator_prec != Precedence_MIN) {
        if (prev_operator_prec >= cur_operator_prec) {
            break;
        }else {
            parser_advance(parser);

            left = parser_parse_inifix_expr(parser, curr_operator, left);
            curr_operator = parser->curr;
            cur_operator_prec = Precedence_Lookup[curr_operator.type];
        }
    }
    return left;
}
