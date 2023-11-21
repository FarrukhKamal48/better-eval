#include <stdio.h>
#include "debug.h"
#include "../source/Lexer.h"

/*
*   Prints the lexmes of all the tokens
*/
void lexer_print_lexemes (Token tokenStream[], int streamEnd) {

    int tokenNum = 0;
    int charNum = 0;

    int strlen = 0;

    while (tokenNum < streamEnd) {

        strlen = (tokenStream[tokenNum].lexeme.str + tokenStream[tokenNum].lexeme.size) - tokenStream[tokenNum].lexeme.str;
        char str[strlen];

        charNum = 0;
        while (charNum < strlen) {
            str[charNum] = *(tokenStream[tokenNum].lexeme.str + charNum);
            charNum++;
        }
        str[strlen] = '\0';

        tokenNum++;

        printf("%s\n", str);
    }
}
