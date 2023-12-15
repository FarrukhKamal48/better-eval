#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "clib.h"

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
        case TokenType_Ident:      printf("%s", lexeme_to_string(token.lexeme)); break;
        case TokenType_Caret:      printf("^"); break;
        case TokenType_Slash:      printf("/"); break;
        case TokenType_Star:       printf("*"); break;
        case TokenType_Modulo:     printf("%%"); break;
        case TokenType_Plus:       printf("+"); break;
        case TokenType_Minus:      printf("-"); break;
        case TokenType_Equal:      printf("="); break;
        case TokenType_ClosePipe:  printf("["); break;
        case TokenType_OpenPipe:   printf("]"); break;
        case TokenType_OpenParen:  printf("("); break;
        case TokenType_CloseParen: printf(")"); break;
        case TokenType_Exclaim:    printf("!"); break;
        case TokenType_ERROR:      printf("ERROR"); break;
    }
}

void parser_print_tree(Node *node, int indent) {
    if (indent == 1) printf("\n");
    for (int i = 0; i < indent; i++) printf("%s  ", colors[0]);

    switch (node->type) {
        case NodeType_ERROR: printf("%s%sERROR\n", colors[1], colors[4]); break;

        case NodeType_Num: {
          printf("%s%f\n", colors[6], node->number);
        } break;
            
        case NodeType_Ident: {
          printf("%s%s%c\n", colors[6], colors[12], (int)node->number);
        } break;

        case NodeType_Positive: {
          printf("%sUnary %s+:\n", colors[6], colors[4]);
          parser_print_tree(node->unary.operand, indent + 1);
        } break;

        case NodeType_Negative: {
          printf("%sUnary %s-:\n", colors[6], colors[4]);
          parser_print_tree(node->unary.operand, indent + 1);
        } break;
            
        case NodeType_Factorial: {
          printf("%sUnary %s!:\n", colors[6], colors[4]);
          parser_print_tree(node->unary.operand, indent + 1);
        } break;

        case NodeType_Abs: {
          printf("%sAbs:\n", colors[4]);
          parser_print_tree(node->unary.operand, indent + 1);
        } break;
            
        case NodeType_Equal: {
          printf("%s=:\n", colors[4]);
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Add: {
          printf("%s+:\n", colors[4]);
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Sub: {
          printf("%s-:\n", colors[4]);
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Mod: {
          printf("%s%%:\n", colors[4]);
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Mul: {
          printf("%s*:\n", colors[4]);
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Div: {
          printf("%s/:\n", colors[4]);
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;

        case NodeType_Pow: {
          printf("%s^:\n", colors[4]);
          parser_print_tree(node->binary.left, indent + 1);
          parser_print_tree(node->binary.right, indent + 1);
        } break;
    }
}

