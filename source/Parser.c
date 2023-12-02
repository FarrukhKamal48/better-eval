#include <stdio.h>
#include <stdlib.h>

#include "Parser.h"
#include "Lexer.h"


static Precedence Precedence_Lookup[TokenType_MAX] = {
    [TokenType_Plus] = Precedence_Term,
    [TokenType_Minus] = Precedence_Term,
    [TokenType_Slash] = Precedence_Factor,
    [TokenType_Star] = Precedence_Factor,
    [TokenType_Caret] = Precedence_Power,
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

Node *parser_parse_inifix_expr(Parser *parser, Token operator, Node *left) {
    Node *ret = Alloc_Node();
    switch (operator.type) {
        case TokenType_Plus:  ret->type = NodeType_Add; break;
        case TokenType_Minus: ret->type = NodeType_Sub; break;
        case TokenType_Star:  ret->type = NodeType_Mul; break;
        case TokenType_Slash: ret->type = NodeType_Div; break;
        case TokenType_Caret: ret->type = NodeType_Pow; break;
    }
    ret->binary.left = left;
    ret->binary.right = parser_parse_expression(parser, Precedence_Lookup[operator.type]);

    printf("\nOperator: ");
    PrintNode(ret);
    printf("\nLeft: ");
    PrintNode(ret->binary.left);
    printf("\nRight: ");
    PrintNode(ret->binary.right);
    printf("\n");

    return ret;
}

Node *parser_parse_expression(Parser *parser, Precedence prev_operator_prec) {
    Node *left = parser_parse_number(parser);
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

Node *Alloc_Node() {
    printf("\n Alocating Node, Size: %ld", sizeof(Node));
    Node *newNode = malloc(sizeof(Node));
    while (newNode == NULL) {
        Node *newNode = malloc(sizeof(Node));
        printf("\n Failed, Re-Alocating Node, Size: %ld", sizeof(Node));
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

void PrintNode (Node *tree) {
    switch (tree->type) {
        case NodeType_Num:  printf("%f", tree->number); break;
        case NodeType_Pow:  printf("^"); break;
        case NodeType_Div:  printf("/"); break;
        case NodeType_Mul:  printf("*"); break;
        case NodeType_Add:  printf("+"); break;
        case NodeType_Sub:  printf("-"); break;
    }
}

void PrintTree(Node *tree) {
    printf("\n");
    
    if (tree->type == NodeType_Num) {
        printf("%f\t", tree->number);
        return;
    }
    PrintNode(tree);
    PrintTree(tree->binary.left);
    PrintTree(tree->binary.right);

    printf("\n");
}
