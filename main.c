#include <stdio.h>
#include "source/Lexer.h"

void Tokanize(Lexer *lexer, Token *TokenStream, int len) {
    int i = 0;
    Token CurrToken = lexer_next_token(lexer);
    while ((CurrToken.type != TokenType_EOF & CurrToken.type != TokenType_ERROR) & (i < len)) {
        TokenStream[i] = CurrToken;
        CurrToken = lexer_next_token(lexer);
        printf("    Start: %c, Len: %d, Type: %d, Size: %lu\n", *TokenStream[i].lexeme.str, TokenStream[i].lexeme.size, TokenStream[i].type, sizeof(TokenStream[0]));

        i++;
    }
    printf("Tokens: %d\n", i);
}

int main(int argc, char *argv[])
{
    // origional expression
    char exp[100];

    // get the expresion
    printf(">> ");
    fgets(exp, 100, stdin);

    // initialize lexer
    Lexer lexer = (Lexer) {
        .start = exp,
        .current = exp,
    };

    // final tokanized list
    Token TokenStream[10000];

    // Populate the token stream
    Tokanize(&lexer, TokenStream, sizeof(TokenStream)/sizeof(TokenStream[0]));

    return 0;
}
