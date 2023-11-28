#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source/eval.h"


int main(int argc, char *argv[])
{
    string expression = (string) {
        .str = argv[1],
        .size = strlen(argv[1])
    };

    // printf("%s\n", expression.str);

    Parser parser;
    parser_init(&parser, expression);
    Node *tree = parser_parse_expression(&parser, Precedence_Min);
    float answer = evaluate(tree);

    free(tree);

    printf("%f\n", answer);

    return 0;
}
