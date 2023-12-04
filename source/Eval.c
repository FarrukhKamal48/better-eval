#include <math.h>

#include "Eval.h"
#include "Parser.h"
#include "../lib/clib.h"

float evaluate(Node *expr) {
    switch (expr->type) {
        case NodeType_Num: return expr->number; break;
        case NodeType_Abs: return Abs(evaluate(expr->unary.operand)); break;
        case NodeType_Positive: return +evaluate(expr->unary.operand); break;
        case NodeType_Negative: return -evaluate(expr->unary.operand); break;
        case NodeType_Pow: return pow(evaluate(expr->binary.left), evaluate(expr->binary.right)); break;
        case NodeType_Div: return evaluate(expr->binary.left) / evaluate(expr->binary.right); break;
        case NodeType_Mul: return evaluate(expr->binary.left) * evaluate(expr->binary.right); break;
        case NodeType_Add: return evaluate(expr->binary.left) + evaluate(expr->binary.right); break;
        case NodeType_Sub: return evaluate(expr->binary.left) - evaluate(expr->binary.right); break;
        case NodeType_ERROR: return FLOAT_MAX; break;
    }
    return 0;
}

