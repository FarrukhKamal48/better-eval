#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

char *lexeme_to_string(string lexeme) {
    char *str = malloc(lexeme.size * sizeof(char));
    for (int i = 0; i < lexeme.size; i++) {
        str[i] = lexeme.str[i];
    }
    str[lexeme.size] = '\0';
    return str;
}
void lexer_print_token(Token token) {
    printf("\n");
    switch (token.type) {
        case TokenType_Num:        printf("%s", lexeme_to_string(token.lexeme)); break;
        case TokenType_Caret:      printf("^"); break;
        case TokenType_Slash:      printf("/"); break;
        case TokenType_Star:       printf("*"); break;
        case TokenType_Modulo:     printf("%%"); break;
        case TokenType_Plus:       printf("+"); break;
        case TokenType_Minus:      printf("-"); break;
        case TokenType_OpenParen:  printf("("); break;
        case TokenType_CloseParen: printf(")"); break;
        case TokenType_Pipe:       printf("|"); break;
        case TokenType_ERROR:      printf("ERROR"); break;
    }
}

void parser_print_tree(Node *node, int indent) {
    if (indent == 0) printf("\n");
    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case NodeType_ERROR: printf("ERROR\n"); break;

        case NodeType_Num: {
          printf("%f\n", node->number);
        } break;

        case NodeType_Positive: {
          printf("Unary +:\n");
          parser_print_tree(node->unary.operand, indent + 1);
        } break;

        case NodeType_Negative: {
          printf("Unary -:\n");
          parser_print_tree(node->unary.operand, indent + 1);
        } break;

        case NodeType_Abs: {
          printf("Abs:\n");
          parser_print_tree(node->unary.operand, indent + 1);
        } break;

        case NodeType_Add: {
          printf("+:\n");
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Sub: {
          printf("-:\n");
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Mod: {
          printf("%%:\n");
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Mul: {
          printf("*:\n");
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Div: {
          printf("/:\n");
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Pow: {
          printf("^:\n");
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;
    }
}

