#include <stdio.h>
#include <string.h>
#include "source/Lexer.h"


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

    return 0;
}
