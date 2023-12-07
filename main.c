#include <stdio.h>

#include "lib/clib.h"
#include "lib/debug.h"
#include "source/Eval.h"
#include "source/Parser.h"

void Calculate(Identifier *ident, string expression, unsigned short int debug);

int main(int argc, char *argv[])
{
    Identifier ident;
    ident_init(&ident);
    
    if (argc == 1) {
        char expr[100];
        while (1) {
            printf("\n%s%s❯ ", colors[1], colors[4]);
            Fgets(expr, 100);
            if (expr[0] == '\\' && expr[1] == 'q') 
                break;
            printf("  ");
            Calculate(&ident, strMake(expr), 1);
        }
    }
    else if (argc == 2) {
        string expression = strMake(argv[1]);
        printf("  %s%s%s", colors[1], colors[4], expression.str);
        Calculate(&ident, expression, 0);
    }
    else if (argc == 3) {
        string expression = strMake(argv[1]);
        printf("  %s%s%s ", colors[1], colors[4], expression.str);
        Calculate(&ident, expression, *argv[2]=='d');
    }
    
    return 0;
}

void Calculate(Identifier *ident, string expression, unsigned short int debug) {
    Parser parser;
    parser_init(&parser, expression);
    Node *tree = parser_parse_expression(&parser, Precedence_MIN);
    float answer = evaluate(tree, ident);
    
    printf("= %s%f\n", colors[6], answer);

    if (debug) parser_print_tree(tree, 1);
    Dealloc_Tree(tree);
}
