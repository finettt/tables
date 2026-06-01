#ifndef MATH_NODE_H
#define MATH_NODE_H
typedef enum {
    MATH_NODE_SUB,
    MATH_NODE_ADD,
    MATH_NODE_MUL,
    MATH_NODE_DIV,
    MATH_NODE_POW,
    MATH_NODE_NUMBER
} MathNodeType;

typedef struct MathNode {
    MathNodeType type;
    union {
        struct {
            struct MathNode* left;
            struct MathNode* right;
        } op;
        double value;
    } data;
} MathNode;

MathNode* math_make_number(double val);
MathNode* math_make_operation(MathNodeType type, MathNode* left, MathNode* right);
double math_compute_graph(MathNode* graph);
void math_free_graph(MathNode* graph);
#endif

