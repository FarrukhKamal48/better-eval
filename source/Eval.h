#ifndef EVAL
#define EVAL

#include "Parser.h"
#include "Ident.h"

#define FLOAT_MAX 340282346638528859811704183484516925440.000000

float evaluate(Node *tree, Identifier *ident);

#endif
