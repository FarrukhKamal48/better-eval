#ifndef EVAL
#define EVAL

#include "Parser.h"
#include "Ident.h"

float evaluate(Node *expr, Identifier **ident, Function **func);

#endif
