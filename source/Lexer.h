#ifndef LEXER
#define LEXER

typedef int TokenType;
enum {
    TokenType_Carret,
    TokenType_Slash,
    TokenType_Star,
    TokenType_Plus,
    TokenType_Minus,

    TokenType_Num,

    TokenType_EOF,
    TokenType_ERROR
};

typedef struct string {
    char *str;
    int size;
} string;

typedef struct Token {
    TokenType type;
    string lexeme;
} Token;

typedef struct Lexer {
    char *start;
    char *current;
} Lexer;

// functions

/*
*   Initialize the lexer
*/
void lexer_init(Lexer *lexer, string expresssion);

/* 
 * Makes a token, using lexer span as a lexeme and type as the tokentype
*/
Token lexer_make_token (Lexer *lexer, TokenType type); 

/* 
 * Makes a number token, following the current span
*/
Token lexer_number_token (Lexer *lexer);

/* 
 * Gives the next token
*/
Token lexer_next_token (Lexer *lexer);

#endif
