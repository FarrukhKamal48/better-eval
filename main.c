#include <stdio.h>

#include "lib/clib.h"
#include "lib/debug.h"
#include "source/Eval.h"
#include "source/Parser.h"

void Calculate(string expression, unsigned short int debug);

int main(int argc, char *argv[])
{
    if (argc == 1) {
        char expr[100];
        while (1) {
            printf("\n>> ");
            Fgets(expr, 100);
            if (expr[0] == '\\' && expr[1] == 'q') 
                break;
            Calculate(strMake(expr), 1);
        }
    }
    else if (argc == 2) {
        string expression = strMake(argv[1]);
        Calculate(expression, 0);
    }
    else if (argc == 3) {
        string expression = strMake(argv[1]);
        Calculate(expression, *argv[2]=='d');
    }

    return 0;
}

void Calculate(string expression, unsigned short int debug) {
    Parser parser;
    parser_init(&parser, expression);
    Node *tree = parser_parse_expression(&parser, Precedence_MIN);
    float answer = evaluate(tree);

    printf("\n%s = %f\n", expression.str, answer);

    if (debug) parser_print_tree(tree, 0);
    Dealloc_Tree(tree);
}
