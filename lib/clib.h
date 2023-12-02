#ifndef clib
#define clib

#include "../source/Lexer.h"

/* 
 * Checks if char is a digit
*/
unsigned short int isDigit(char a); 

/* 
 * Checks if char is whitespace
*/
unsigned short int isWhitspace(char a); 

/*
*   returns a string struct from string
*/
string strMake(char str[]);

#endif
