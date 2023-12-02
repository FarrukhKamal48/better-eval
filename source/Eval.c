#include <math.h>

#include "Eval.h"
#include "Parser.h"

float evaluate(Node *tree) {
    switch (tree->type) {
        case NodeType_Num: return tree->number; break;
        case NodeType_Positive: return +evaluate(tree->unary.operand); break;
        case NodeType_Negative: return -evaluate(tree->unary.operand); break;
        case NodeType_Pow: return pow(evaluate(tree->binary.left), evaluate(tree->binary.right)); break;
        case NodeType_Div: return evaluate(tree->binary.left) / evaluate(tree->binary.right); break;
        case NodeType_Mul: return evaluate(tree->binary.left) * evaluate(tree->binary.right); break;
        case NodeType_Add: return evaluate(tree->binary.left) + evaluate(tree->binary.right); break;
        case NodeType_Sub: return evaluate(tree->binary.left) - evaluate(tree->binary.right); break;
    }
    return 0;
}

