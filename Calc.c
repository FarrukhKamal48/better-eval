#include <stdio.h>
#include "source/Lexer.h"

int main(int argc, char *argv[])
{
    char exp[100];

    // get the expresion
    printf("> ");
    scanf("%s", exp);

    // initialize lexer
    Lexer lexer = (Lexer) {
        .start = exp,
        .current = exp,
    };

    Token TokenStream[10000];

    int i = 0;
    Token CurrToken = lexer_next_token(&lexer);
    while ((CurrToken.type != TokenType_EOF & CurrToken.type != TokenType_ERROR) & (i < sizeof(TokenStream)/sizeof(TokenStream[0]))) {
        TokenStream[i] = CurrToken;
        CurrToken = lexer_next_token(&lexer);
        printf("    Start: %c, Len: %d, Type: %d, Size: %lu\n", *TokenStream[i].lexeme.str, TokenStream[i].lexeme.size, TokenStream[i].type, sizeof(TokenStream[0]));

        i++;
    }
    printf("Tokens: %d\n", i);

    return 0;
}
