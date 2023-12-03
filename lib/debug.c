#include <stdio.h>

#include "debug.h"

void parser_print_tree(Node *node, int indent) {
    if (indent == 0) printf("\n");
    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case NodeType_ERROR: printf("Error\n"); break;

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

