#include "Lexer.h"
#include "../lib/clib.h"


void lexer_init(Lexer *lexer, string expresssion) {
    lexer->start = expresssion.str;
    lexer->current = expresssion.str;
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
    unsigned short int dps = 0;
    while (isDigit(*lexer->current) || (*lexer->current == '.')) {
        dps += *lexer->current == '.';
        lexer->current += 1;
    }
    if (dps > 1) return lexer_make_token(lexer, TokenType_ERROR);
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

        case '%': lexer->current++; return lexer_make_token(lexer, TokenType_Modulo); 

        case '(': lexer->current++; return lexer_make_token(lexer, TokenType_OpenParen); 
        case ')': lexer->current++; return lexer_make_token(lexer, TokenType_CloseParen); 

        case '|': lexer->current++; return lexer_make_token(lexer, TokenType_Pipe); 

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return lexer_number_token(lexer);

        default: return lexer_make_token(lexer, TokenType_ERROR);
    }
}
