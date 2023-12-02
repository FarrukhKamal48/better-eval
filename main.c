#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "source/Eval.h"
#include "source/Parser.h"

int main(int argc, char *argv[])
{
    string expression = (string) {
        .str = argv[1],
        .size = strlen(argv[1])
    };
    printf("%s\n", expression.str);

    Lexer lexer;
    lexer_init(&lexer, expression);

    Token currToken = lexer_next_token(&lexer);
    while (currToken.type != TokenType_EOF) {
        lexer_print_token(currToken);
        currToken = lexer_next_token(&lexer);
    }


    Node tree;
    tree.type = NodeType_Add;
    // PrintNode(&tree);

    tree.binary.left = malloc(sizeof(Node));
    tree.binary.left->type = NodeType_Add;

    tree.binary.left->binary.left = malloc(sizeof(Node));
    tree.binary.left->binary.left->type = NodeType_Num;
    tree.binary.left->binary.left->number = 8;

    tree.binary.left->binary.right = malloc(sizeof(Node));
    tree.binary.left->binary.right->type = NodeType_Num;
    tree.binary.left->binary.right->number = 7;
    // PrintNode(tree.binary.left);

    tree.binary.right = malloc(sizeof(Node));
    tree.binary.right->type = NodeType_Num;
    tree.binary.right->number = 10;
    // PrintNode(tree.binary.right);

    PrintTree(&tree);

    float answer = evaluate(&tree);
    printf("\nAnswer\n: %f", answer);

    Dealloc_Tree(&tree);

    return 0;
}
