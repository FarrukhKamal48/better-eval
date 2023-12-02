#include <stdio.h>
#include <stdlib.h>

#include "Parser.h"

void Dealloc_Tree(Node *tree) {
    if (tree->type == NodeType_Num) { 
        free(tree); 
        return;
    }
    
    Dealloc_Tree(tree->binary.left);
    Dealloc_Tree(tree->binary.right);
};

void PrintNode (Node *tree) {
    switch (tree->type) {
        case NodeType_Num:  printf("%f", tree->number); break;
        case NodeType_Pow:  printf("^"); break;
        case NodeType_Div:  printf("/"); break;
        case NodeType_Mul: printf("*"); break;
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
}
