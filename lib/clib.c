#include "clib.h"

/* 
 * Checks if char is a digit
*/
unsigned short int isDigit(char a) {
    switch (a) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': return 1;

        default: return 0;
    }
}

/* 
 * Checks if char is whitespace
*/
unsigned short int isWhitspace(char a) {
    switch (a) {
        case ' ': case '\r': case '\t': case '\n': return 1; 

        default: return 0;
    }
}; 
