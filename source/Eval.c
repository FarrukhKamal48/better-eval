#include <math.h>

#include "Eval.h"
#include "../lib/clib.h"
#include "Ident.h"

float SetIdentifier(Node *varNode, Node *expression, Identifier **ident, Function **func);
float RecalIdentifier(char letter, Identifier **ident);
float RecalFunction(Node *expr, Identifier **ident, Function **func);

float evaluate(Node *expr, Identifier **ident, Function **func) {
    switch (expr->type) {
        case NodeType_Num:       return expr->number; break;
        case NodeType_Ident:     return RecalIdentifier(expr->letters[0], ident); break;
        case NodeType_Func:      return RecalFunction(expr, ident, func); break;
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


float RecalIdentifier(char letter, Identifier **ident) {
    Identifier *curr = ident_find(*ident, letter);
    if (curr == NUL) return FLOAT_MAX;
    else
        return curr->value;
}
float RecalFunction(Node *func_node, Identifier **ident, Function **func) {
    Function *curr_func = func_find(*func, func_node->letters[0]);
    if (curr_func == NUL) return FLOAT_MAX;     // get the stored function

    Identifier *arg_ident = ident_find(*ident, '_');  // get the special function identifier
    if (arg_ident == NUL) return FLOAT_MAX;
    
    if (func_node->letters[1]=='\0')                  // get argument as explicitly typed by user (eg. f(20))
        arg_ident->value = func_node->number;
    else if (func_node->letters[1] != curr_func->arg) {     // if user enters previously defined variable
        Identifier *new = ident_find(*ident, func_node->letters[1]);
        if (new == NUL) arg_ident->value = FLOAT_MAX;        // weirdly enough, this somehow adds support for composite functions
        else
            arg_ident->value = new->value;                  
    }

    return evaluate(curr_func->expr, ident, func);      // evaluate function
}
float SetIdentifier(Node *varNode, Node *expression, Identifier **ident, Function **func) {
    if (varNode->type == NodeType_Ident) {
        char letter = varNode->letters[0]; 
        Identifier *curr = ident_find(*ident, letter);
        
        if (curr == NUL) curr = ident_add(ident, letter, evaluate(expression, ident, func));
        else
            curr->value = evaluate(expression, ident, func);
        
        return curr->value;
    }
    else if (varNode->type == NodeType_Func) {
        char letter = varNode->letters[0];
        char arg = varNode->letters[1];
        Function *curr = func_find(*func, letter);
        
        if (curr == NUL) curr = func_add(func, letter, arg, expression);
        else
            curr->expr = expression;
        
        Identifier *arg_ident = ident_find(*ident, '_');
        ident_node_replace(curr->expr, curr->arg, arg_ident->letter, arg_ident->value);
    }
    return INF;
}

