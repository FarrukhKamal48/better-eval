#include "../lib/clib.h"
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
        char letter = *parser->curr.lexeme.str;
        parser_advance(parser);
        if (parser->curr.type == TokenType_OpenParen) {
            parser_advance(parser);
            
            ret = Alloc_Node();
            ret->type = NodeType_Func;
            ret->letters[0] = letter;
            if (isDigit(*parser->curr.lexeme.str)) {
                ret->letters[1] = '\0';
                ret->number = lexeme_to_number(parser->curr.lexeme);
            }
            else ret->letters[1] = *parser->curr.lexeme.str;
            
            parser_advance(parser);
            parser_advance(parser);
        }
        else {
            ret = Alloc_Node();
            ret->type = NodeType_Ident;
            ret->letters[0] = letter;
        }
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

    if (parser->curr.type == TokenType_Exclaim) {
        parser_advance(parser);
        Node *fact_ret = Alloc_Node();
        fact_ret->type = NodeType_Factorial;
        fact_ret->unary.operand = ret;
        ret = fact_ret;
    }
    
    if (parser->curr.type == TokenType_Num || parser->curr.type == TokenType_Ident || 
        parser->curr.type == TokenType_OpenParen || parser->curr.type == TokenType_OpenPipe) {
        Node *mult_ret = Alloc_Node();
        mult_ret->type = NodeType_Mul;
        mult_ret->binary.left = ret; 
        mult_ret->binary.right = parser_parse_expression(parser, Precedence_Lookup[Precedence_Factor]);
        ret = mult_ret;
    }
    
    return ret;
}

Node *parser_parse_binary_operator(Parser *parser, Token operator, Node *left) {
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

            left = parser_parse_binary_operator(parser, curr_operator, left);
            curr_operator = parser->curr;
            cur_operator_prec = Precedence_Lookup[curr_operator.type];
        }
    }
    return left;
}

void ident_node_replace(Node *expr, char prev_letter, char new_letter, float new_number) {
    if (expr->type == NodeType_Num || expr->type == NodeType_ERROR || expr->type == NodeType_Func)
        return;
    else if (expr->type == NodeType_Ident && expr->letters[0] == prev_letter) {
        expr->letters[0] = new_letter;
        expr->number = new_number;
    }
    else if (expr->type == NodeType_Positive || expr->type == NodeType_Negative || 
        expr->type == NodeType_Abs || expr->type == NodeType_Factorial) {
        ident_node_replace(expr->unary.operand, prev_letter, new_letter, new_number);
    }
    else if (expr->type == NodeType_Pow || expr->type == NodeType_Div || 
        expr->type == NodeType_Mul || expr->type == NodeType_Mod || expr->type == NodeType_Add || 
        expr->type == NodeType_Sub || expr->type == NodeType_Equal) {
        ident_node_replace(expr->binary.left, prev_letter, new_letter, new_number);
        ident_node_replace(expr->binary.right, prev_letter, new_letter, new_number);
    }
    return;
}
