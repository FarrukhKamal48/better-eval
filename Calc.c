#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int TokenType;
enum {
    TokenType_Star,
    TokenType_Slash,
    TokenType_Plus,
    TokenType_Minus,

    TokenType_EOF,
    TokenType_ERROR
};

typedef struct string {
    char *str;
    int size;
} string;

typedef struct Token {
    TokenType type;
    char *lexeme;
} Token;

typedef struct Lexer {
    char *start;
    char *current;
} Lexer;

void lexer_make_lexeme (Lexer *lexer, Token *token) {
    int len = lexer->current - lexer->start;
    token->lexeme = (char*) malloc(len * sizeof(char));

    for (int i = 0; i < lexer->current - lexer->start; ++i) {
        token->lexeme[i] = *(lexer->start + i);
    }
}

Token lexer_make_token (Lexer *lexer, TokenType type) {
    Token newToken = (Token) {
        .type = type,
    };
    lexer_make_lexeme(lexer, &newToken);

    return newToken;
}

Token lexer_next_token (Lexer *lexer) {
    lexer->current = lexer->start;

    if (*lexer->current == '\0') 
        return lexer_make_token(lexer, TokenType_EOF);

    switch (*lexer->current) {
        case '/': lexer->current++; return lexer_make_token(lexer, TokenType_Slash); 
        case '*': lexer->current++; return lexer_make_token(lexer, TokenType_Star); 
        case '+': lexer->current++; return lexer_make_token(lexer, TokenType_Plus); 
        case '-': lexer->current++; return lexer_make_token(lexer, TokenType_Minus); 

        default: return lexer_make_token(lexer, TokenType_ERROR);
    }
}

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
    Token CurrToken = lexer_next_token(&lexer);
    printf("%s", CurrToken.lexeme);

    // int i;
    // while ((CurrToken.type != TokenType_EOF & CurrToken.type != TokenType_ERROR) & (i < sizeof(TokenStream)/sizeof(TokenStream[0]))) {
    //     TokenStream[i] = CurrToken;
    //     CurrToken = lexer_next_token(&lexer);
    //     i++;
    //
    //     printf("%s", CurrToken.lexeme);
    // }

    // char test[] = "0123456789";
    // int start = 1;
    // int current = 1;
    // char lexerem[current-start+1];
    // lexer_make1_lexeme(start, current, lexerem, test);
    // printf("%c", lexerem[0]);
    // printf("%c", lexerem[1]);

    return 0;
}
