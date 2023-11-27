#ifndef LEXER
#define LEXER

typedef int TokenType;
enum {
    TokenType_Caret,
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

void lexer_init(Lexer *lexer, string expresssion);

Token lexer_make_token (Lexer *lexer, TokenType type); 

Token lexer_number_token (Lexer *lexer);

Token lexer_next_token (Lexer *lexer);

float lexeme_to_number (string lexeme);

#endif
