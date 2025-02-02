#ifndef LEXER
#define LEXER

typedef int TokenType;
enum {
    TokenType_Caret,
    TokenType_Slash,
    TokenType_Star,
    TokenType_Modulo,
    TokenType_Plus,
    TokenType_Minus,
    TokenType_Equal,

    TokenType_Num,
    TokenType_Ident,
    TokenType_Comma,

    TokenType_OpenPipe,
    TokenType_ClosePipe,
    TokenType_OpenParen,
    TokenType_CloseParen,
    TokenType_Exclaim,

    TokenType_EOF,
    TokenType_ERROR,
    TokenType_MAX,
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


void lexer_init(Lexer *lexer, string expresssion);
Token lexer_make_token (Lexer *lexer, TokenType type); 
Token lexer_number_token (Lexer *lexer);
Token lexer_next_token (Lexer *lexer);

#endif
