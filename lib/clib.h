#ifndef clib
#define clib

#include "../source/Parser.h"

unsigned short int isDigit(char a); 
unsigned short int isAlpha(char a); 
unsigned short int isWhitspace(char a); 

string strMake(char str[]);
float Abs(float val);
void Fgets(char *str, int size);

float lexeme_to_number (string lexeme);

Node *Alloc_Node();
void Dealloc_Tree(Node *tree);

#endif
