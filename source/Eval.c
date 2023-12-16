#include <math.h>

#include "Eval.h"
#include "Ident.h"
#include "Parser.h"
#include "../lib/clib.h"

float SetIdentifier(Node *identifier, Node *expression, Identifier *ident, Function *func);
float RecalIdentifier(char letter, Identifier *ident);
// float RecalFunction(float number, Function *func);

float evaluate(Node *expr, Identifier *ident, Function *func) {
    switch (expr->type) {
        case NodeType_Num:       return expr->number; break;
        case NodeType_Ident:     return RecalIdentifier(expr->letter, ident); break;
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
float SetIdentifier(Node *identifier, Node *expression, Identifier *ident, Function *func) {
    if (identifier->type == NodeType_Ident) {
        int letter = identifier->letter; 
        Identifier *curr_Ident = ident_find(ident, letter);
        if (curr_Ident == ((void*)0))
            curr_Ident = ident_add(ident, letter, evaluate(expression, ident, func));
        else
            curr_Ident->value = evaluate(expression, ident, func);
        
        return curr_Ident->value;
    }
    else if (identifier->type == NodeType_Func) {
        char letter = (int)(identifier->number/100);
        char arg = Ceil((identifier->number/100 - letter)*100);
        Function *curr_func = func_find(func, letter);
        if (curr_func == ((void*)0))
            curr_func = func_add(func, letter, arg, expression);
        else {
            curr_func->expr = expression;
        }
    }
    return FLOAT_MAX;
}

