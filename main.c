#include <stdio.h>

#include "lib/clib.h"
#include "lib/debug.h"
#include "source/Eval.h"
#include "source/Parser.h"

void Calculate(Identifier *ident, string expression, unsigned short int debug);

int main(int argc, char *argv[])
{
    unsigned short int flags[3][2] = {0};
    for (int i = 1; i < argc; i++) {        // get all flags like debug or help
        switch (argv[i][0]) {
            default: flags[0][0] = 1; flags[0][1] = i; break;   // expression
            case 'd': flags[1][0] = 1; flags[1][1] = i; break;  // debug
            case 'h': flags[2][0] = 1; flags[2][1] = i; break;  // help
        }
    }
    
    char help_msg[250] = "\n^,*,/,+,-     -- basic arithmatic operators \n%             -- Modulus operator(remainder) \n=             -- used for variable assighnment (eg. x = 5) \n()            -- parenthes (self explanitory) \n[]            -- Absolute operator ([-5] = 5)\n";
    if (flags[2][0]) {      // print help message
        printf("%s%s", colors[5], help_msg);
        if (argc == 2) return 0;
    }

    Identifier ident;       // setup identifier list
    ident_init(&ident);
    
    if (flags[0][0]) {                                      // if expression has been provided
        string expression = strMake(argv[flags[0][1]]);     // get the expression
        printf("  %s%s%s", colors[1], colors[4], expression.str);
        Calculate(&ident, expression, flags[1][0]);         // start calculation (while also checking for debug flag)
    }
    else {                                              // if no expression provided
        char expr[100];
        printf("\n");
        while (1) {
            if (flags[1][0]) printf("\n");
            printf("%s❯ %s%s", colors[6], colors[1], colors[4]);   // print sylish prompt
            Fgets(expr, 100);                           // get the expression
            printf("  ");       // padding
            
            if (expr[0] == '\\' && expr[1] == 'q')      // quit
                break;
            if (expr[0] == '\\' && expr[1] == 'h') {    // print help
                printf("%s%s", colors[5], help_msg);
                continue;
            }
            if (expr[0] == '\\' && expr[1] == 'd') {    // toggle debug
                flags[1][0] = !flags[1][0];
                if (!flags[1][0]) printf("\n");
                continue;
            }
            
            Calculate(&ident, strMake(expr), flags[1][0]);  // start the calculation
        }
    }
    printf("\n");
    
    return 0;
}

void Calculate(Identifier *ident, string expression, unsigned short int debug) {
    Parser parser;
    parser_init(&parser, expression);
    Node *tree = parser_parse_expression(&parser, Precedence_MIN);
    float answer = evaluate(tree, ident);
    
    if (answer >= FLOAT_MAX) printf("%s%sERROR\n", colors[1], colors[3]);
    else
        printf("= %s%f\n", colors[6], answer);

    if (debug) parser_print_tree(tree, 1);
    Dealloc_Tree(tree);
}
