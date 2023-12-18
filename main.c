#include <stdio.h>

#include "lib/clib.h"
#include "lib/debug.h"
#include "source/Eval.h"

void Calculate(Identifier **ident, Function **func, string expression, unsigned short int debug);

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
    
    char help_msg[300] = "\n^ * / + -     -- basic arithmatic operators \n!             -- Factorial \n%             -- Modulus operator(remainder) \n=             -- used for variables and fucntions (eg. x = 5, f(x) = 5x) \n()            -- parenthes (self explanitory) \n[]            -- Absolute operator ([-5] = 5)\n";
    if (flags[2][0]) {      // print help message
        printf("%s%s", colors[5], help_msg);
        if (argc == 2) return 0;
    }

    Identifier *ident = NULL;       // setup identifier list
    ident_add(&ident, '_', 0);      // used to store function arguments
    
    Function *func = NULL;          // setup funciton list
    
    if (flags[0][0]) {                                      // if expression has been provided
        string expression = strMake(argv[flags[0][1]]);     // get the expression
        printf("  %s%s%s", colors[1], colors[4], expression.str);
        Calculate(&ident, &func, expression, flags[1][0]);         // start calculation (while also checking for debug flag)
    }
    else {                                              // if no expression provided
        char expr[100];
        printf("\n");
        while (1) {
            if (flags[1][0]) printf("\n");      // go to new line if debug toggled
            printf("%s❯ %s%s", colors[6], colors[1], colors[4]);   // print sylish prompt
            Fgets(expr, 100);                           // get the expression
            printf("  ");       // padding
            
            if (expr[0] == '\\') {
                if (expr[1] == 'q')      // quit
                    break;
                if (expr[1] == 'h') {    // print help
                    printf("%s%s", colors[5], help_msg);
                    continue;
                }
                if (expr[1] == 'd') {    // toggle debug
                    flags[1][0] = !flags[1][0];
                    if (!flags[1][0]) printf("\n");
                    continue;
                }
                if (expr[1] == 'v') {    // print all set variables
                    printf("%s", colors[5]);
                    printIdent(&ident);
                    printf("%s", colors[0]);
                    continue;
                }
                if (expr[1] == 'f') {    // print all declared functions 
                    printf("%s", colors[5]);
                    printFunc(&func);
                    printf("%s", colors[0]);
                    continue;
                }
            }
            
            Calculate(&ident, &func, strMake(expr), flags[1][0]);  // start the calculation
        }
    }
    printf("\n");
    
    return 0;
}

void Calculate(Identifier **ident, Function **func, string expression, unsigned short int debug) {
    Parser parser;
    parser_init(&parser, expression);
    Node *tree = parser_parse_expression(&parser, Precedence_MIN);
    float answer = evaluate(tree, ident, func);
    
    if (answer >= INF)       printf("");
    else if (answer >= FLOAT_MAX) printf("%s%sERROR\n", colors[1], colors[3]);
    else
        printf("= %s%f\n", colors[6], answer);

    if (debug) parser_print_tree(tree, 1);
    Dealloc_Tree(tree);
}
