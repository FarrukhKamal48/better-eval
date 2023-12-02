#include <stdlib.h>
#include <stdio.h>

#include "lib/clib.h"
#include "source/Eval.h"
#include "source/Lexer.h"
#include "source/Parser.h"

void Make_Tree(Node *tree);

int main(int argc, char *argv[])
{
    string expression = strMake(argv[1]);
    printf("%s\n", expression.str);

    // Lexer lexer;
    // lexer_init(&lexer, expression);
    //
    // Token currToken = lexer_next_token(&lexer);
    // while (currToken.type != TokenType_EOF) {
    //     lexer_print_token(currToken);
    //     currToken = lexer_next_token(&lexer);
    // }


    // Node *tree = malloc(sizeof(Node));
    //
    // Make_Tree(tree);
    // PrintTree(tree);
    //
    // float answer = evaluate(tree);
    // printf("\nAnswer: %f\n", answer);
    //
    // Dealloc_Tree(tree);

    Parser parser;
    parser_init(&parser, expression);
    Node *tree = parser_parse_expression(&parser, Precedence_MIN);
    float answer = evaluate(tree);
    printf("\nAnswer: %f\n", answer);

    // PrintTree(tree);
    Dealloc_Tree(tree);

    return 0;
}

