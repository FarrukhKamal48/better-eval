#include <math.h>

#include "Eval.h"
#include "Ident.h"
#include "Parser.h"
#include "../lib/clib.h"

float SetIdentifier(Node *identifier, Node *expression, Identifier *ident);
float RecalIdentifier(float number, Identifier *ident);

float evaluate(Node *expr, Identifier *ident) {
    switch (expr->type) {
        case NodeType_Num:       return expr->number; break;
        case NodeType_Ident:     return RecalIdentifier(expr->number, ident); break;
        case NodeType_Abs:       return Abs(evaluate(expr->unary.operand, ident)); break;
        case NodeType_Positive:  return +evaluate(expr->unary.operand, ident); break;
        case NodeType_Negative:  return -evaluate(expr->unary.operand, ident); break;
        case NodeType_Factorial: return Fact(evaluate(expr->unary.operand, ident)); break;
        case NodeType_Pow:       return pow(evaluate(expr->binary.left, ident), evaluate(expr->binary.right, ident)); break;
        case NodeType_Div:       return evaluate(expr->binary.left, ident) / evaluate(expr->binary.right, ident); break;
        case NodeType_Mul:       return evaluate(expr->binary.left, ident) * evaluate(expr->binary.right, ident); break;
        case NodeType_Mod:       return (int)evaluate(expr->binary.left, ident) % (int)evaluate(expr->binary.right, ident); break;
        case NodeType_Add:       return evaluate(expr->binary.left, ident) + evaluate(expr->binary.right, ident); break;
        case NodeType_Sub:       return evaluate(expr->binary.left, ident) - evaluate(expr->binary.right, ident); break;
        case NodeType_Equal:     return SetIdentifier(expr->binary.left, expr->binary.right, ident); break;
        case NodeType_ERROR:     return FLOAT_MAX; break;
    }
    return 0;
}

float RecalIdentifier(float number, Identifier *ident) {
    int letter_ascii = number;
    Identifier *curr_Ident = ident_find(ident, letter_ascii);
    if (curr_Ident == ((void*)0))
        return FLOAT_MAX;
    else
        return curr_Ident->value;
}
float SetIdentifier(Node *identifier, Node *expression, Identifier *ident) {
    int letter_ascii = identifier->number; 
    Identifier *curr_Ident = ident_find(ident, letter_ascii);
    if (curr_Ident == ((void*)0))
        curr_Ident = ident_add(ident, letter_ascii, evaluate(expression, ident));
    else
        curr_Ident->value = evaluate(expression, ident);
    
    return curr_Ident->value;
}

