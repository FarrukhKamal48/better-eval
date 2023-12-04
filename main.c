#include <stdio.h>

#include "lib/clib.h"
#include "lib/debug.h"
#include "source/Eval.h"
#include "source/Parser.h"

void Calculate(string expression);

int main(int argc, char *argv[])
{
    if (argc == 2) {
        string expression = strMake(argv[1]);
        Calculate(expression);
    }
    else if (argc == 1) {
        char expr[100];
        while (1) {
            printf("\n>> ");
            fgets(expr, 100, stdin);
            if (expr[0] == 'q') 
                break;
            Calculate(strMake(expr));
        }
    }

    return 0;
}

void Calculate(string expression) {
    Parser parser;
    parser_init(&parser, expression);
    Node *tree = parser_parse_expression(&parser, Precedence_MIN);
    float answer = evaluate(tree);

    expression.str[expression.size-1] = '\0';
    printf("%s = %f\n", expression.str, answer);

    parser_print_tree(tree, 0);
    Dealloc_Tree(tree);
}
