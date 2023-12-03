#include <stdio.h>

#include "lib/clib.h"
#include "source/Eval.h"
#include "source/Parser.h"

void Make_Tree(Node *tree);

int main(int argc, char *argv[])
{
    string expression = strMake(argv[1]);
    printf("%s\n", expression.str);

    Parser parser;
    parser_init(&parser, expression);
    Node *tree = parser_parse_expression(&parser, Precedence_MIN);
    parser_print_tree(tree, 0);

    float answer = evaluate(tree);
    printf("\nAnswer: %f\n", answer);

    Dealloc_Tree(tree);

    return 0;
}

