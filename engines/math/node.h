#ifndef NODE_H
#define NODE_H
typedef enum {
    NODE_SUB,
    NODE_ADD,
    NODE_MUL,
    NODE_DIV,
    NODE_POW,
    NODE_NUMBER
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
double math_comute_graph(MathNode* graph);
void math_free_graph(MathNode* graph);
#endif

