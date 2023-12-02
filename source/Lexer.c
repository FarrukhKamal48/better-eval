#include <stdio.h>

#include "Lexer.h"
#include "../lib/clib.h"


void lexer_init(Lexer *lexer, string expresssion) {
    lexer->start = expresssion.str;
    lexer->current = expresssion.str;
};

void lexer_print_token(Token token) {
    int len = (token.lexeme.str + token.lexeme.size) - token.lexeme.str;
    char str[len];
    int i = 0;
    while (i < len) {
        str[i] = *(token.lexeme.str + i);
        i++;
    }
    str[len] = '\0';
    printf("%s\n", str);
};

Token lexer_make_token (Lexer *lexer, TokenType type) {
    Token newToken = (Token) {
        .type = type,
        .lexeme = (string) {
            .str = lexer->start,
            .size = (int)(lexer->current - lexer->start),
        }
    };

    return newToken;
}

Token lexer_number_token (Lexer *lexer) {
    while (isDigit(*lexer->current) | (*lexer->current == '.')) {
        lexer->current += 1;
    }
    return lexer_make_token(lexer, TokenType_Num);
}

Token lexer_next_token (Lexer *lexer) {
    lexer->start = lexer->current;

    while (isWhitspace(*lexer->current) && *lexer->current != '\0') {
        lexer->current++;
        lexer->start = lexer->current;
    }

    if (*lexer->current == '\0') 
        return lexer_make_token(lexer, TokenType_EOF);

    switch (*lexer->current) {
        case '^': lexer->current++; return lexer_make_token(lexer, TokenType_Caret); 
        case '/': lexer->current++; return lexer_make_token(lexer, TokenType_Slash); 
        case '*': lexer->current++; return lexer_make_token(lexer, TokenType_Star); 
        case '+': lexer->current++; return lexer_make_token(lexer, TokenType_Plus); 
        case '-': lexer->current++; return lexer_make_token(lexer, TokenType_Minus); 

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return lexer_number_token(lexer);

        default: return lexer_make_token(lexer, TokenType_ERROR);
    }
}

float lexeme_to_number (string lexeme) {
    float result;
    for (int i = 0; i < lexeme.size; i++) {
        result = result * 10 + (lexeme.str[i] - '0');
    }
    return result;
};
