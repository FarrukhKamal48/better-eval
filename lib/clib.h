#ifndef clib
#define clib

#include "../source/Parser.h"

#define FLOAT_MAX 340282346638528859811704183484516925440.000000

static char colors[13][8] = {
    "\033[0;0m",     // 0 normal
    "\033[0;1m",     // 1 brighter
    "\033[0;32m",    // 2 green   fg
    "\033[0;31m",    // 3 red     fg
    "\033[0;34m",    // 4 blue    fg
    "\033[0;35m",    // 5 purple  fg
    "\033[0;36m",    // 6 cyan    fg
     
    "\033[41m",    // 7 red     bg
    "\033[42m",    // 8 green   bg
    "\033[44m",    // 9 blue    bg
    "\033[45m",    // 10 purple    bg
    "\033[46m",    // 11 cyan    bg
    
    "\033[4m",    // 12 underline
};

unsigned short int isDigit(char a); 
unsigned short int isAlpha(char a); 
unsigned short int isWhitspace(char a); 

string strMake(char str[]);
void Fgets(char *str, int size);

float Abs(float val);
float Fact(float val);

float lexeme_to_number (string lexeme);

Node *Alloc_Node();
void Dealloc_Tree(Node *tree);

#endif
