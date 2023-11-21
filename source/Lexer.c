#include "Lexer.h"

/* 
 * Checks if char is a digit
*/
unsigned short int isDigit(char a) {
    switch (a) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return 1;

        default: return 0;
    }
}

/* 
 * Makes a token, using lexer span as a lexeme and type as the tokentype
*/
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

/* 
 * Makes a number token, following the current span
*/
Token lexer_number_token (Lexer *lexer) {
    while (isDigit(*lexer->current) | (*lexer->current == '.')) {
        lexer->current += 1;
    }
    return lexer_make_token(lexer, TokenType_Num);
}

/* 
 * Gives the next token
*/
Token lexer_next_token (Lexer *lexer) {
    lexer->start = lexer->current;

    if (*lexer->current == '\0') 
        return lexer_make_token(lexer, TokenType_EOF);

    switch (*lexer->current) {
        case '/': lexer->current++; return lexer_make_token(lexer, TokenType_Slash); 
        case '*': lexer->current++; return lexer_make_token(lexer, TokenType_Star); 
        case '+': lexer->current++; return lexer_make_token(lexer, TokenType_Plus); 
        case '-': lexer->current++; return lexer_make_token(lexer, TokenType_Minus); 

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return lexer_number_token(lexer);

        default: return lexer_make_token(lexer, TokenType_ERROR);
    }
}
