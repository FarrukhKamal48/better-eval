#ifndef DEBUG
#define DEBUG

#include "../source/Parser.h"


char *lexeme_to_string(string lexeme);
void lexer_print_token(Token *token);

void parser_print_tree(Node *tree, int indent);

#endif

