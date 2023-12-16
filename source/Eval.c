#include <math.h>

#include "Eval.h"
#include "Ident.h"
#include "Parser.h"
#include "../lib/clib.h"

float SetIdentifier(Node *identifier, Node *expression, Identifier *ident, Function *func);
float RecalIdentifier(char letter, Identifier *ident);
float RecalFunction(char letter, Function *func);

float evaluate(Node *expr, Identifier *ident, Function *func) {
    switch (expr->type) {
        case NodeType_Num:       return expr->number; break;
        case NodeType_Ident:     return RecalIdentifier(expr->letters[0], ident); break;
        // case NodeType_Func:      return RecalFunction(expr->number, func); break;
        case NodeType_Abs:       return Abs(evaluate(expr->unary.operand, ident, func)); break;
        case NodeType_Positive:  return +evaluate(expr->unary.operand, ident, func); break;
        case NodeType_Negative:  return -evaluate(expr->unary.operand, ident, func); break;
        case NodeType_Factorial: return Fact(evaluate(expr->unary.operand, ident, func)); break;
        case NodeType_Pow:       return pow(evaluate(expr->binary.left, ident, func), evaluate(expr->binary.right, ident, func)); break;
        case NodeType_Div:       return evaluate(expr->binary.left, ident, func) / evaluate(expr->binary.right, ident, func); break;
        case NodeType_Mul:       return evaluate(expr->binary.left, ident, func) * evaluate(expr->binary.right, ident, func); break;
        case NodeType_Mod:       return (int)evaluate(expr->binary.left, ident, func) % (int)evaluate(expr->binary.right, ident, func); break;
        case NodeType_Add:       return evaluate(expr->binary.left, ident, func) + evaluate(expr->binary.right, ident, func); break;
        case NodeType_Sub:       return evaluate(expr->binary.left, ident, func) - evaluate(expr->binary.right, ident, func); break;
        case NodeType_Equal:     return SetIdentifier(expr->binary.left, expr->binary.right, ident, func); break;
        case NodeType_ERROR:     return FLOAT_MAX; break;
    }
    return 0;
}


float RecalIdentifier(char letter, Identifier *ident) {
    Identifier *curr_Ident = ident_find(ident, letter);
    if (curr_Ident == ((void*)0))
        return FLOAT_MAX;
    else
        return curr_Ident->value;
}
float SetIdentifier(Node *varNode, Node *expression, Identifier *ident, Function *func) {
    if (varNode->type == NodeType_Ident) {
        int ident_letter = varNode->letters[0]; 
        Identifier *curr_Ident = ident_find(ident, ident_letter);
        if (curr_Ident == ((void*)0))
            curr_Ident = ident_add(ident, ident_letter, evaluate(expression, ident, func));
        else
            curr_Ident->value = evaluate(expression, ident, func);
        
        return curr_Ident->value;
    }
    else if (varNode->type == NodeType_Func) {
        char name = varNode->letters[0];
        char arg = varNode->letters[1];
        Function *curr_func = func_find(func, name);
        if (curr_func == ((void*)0))
            curr_func = func_add(func, name, arg, expression);
        else {
            curr_func->expr = expression;
        }
    }
    return FLOAT_MAX;
}

