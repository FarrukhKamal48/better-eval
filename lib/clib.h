#ifndef clib
#define clib

#include "../source/Parser.h"

unsigned short int isDigit(char a); 
unsigned short int isWhitspace(char a); 
string strMake(char str[]);

float lexeme_to_number (string lexeme);

Node *Alloc_Node();
void Dealloc_Tree(Node *tree);

#endif
