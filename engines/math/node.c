#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include <math.h>

MathNode* math_make_number(double val) {
    MathNode* new_node = (MathNode*)malloc(sizeof(MathNode));
    new_node->type = NODE_NUMBER;
    new_node->data.value = val;
    return new_node;
}

MathNode* math_make_operation(MathNodeType type, MathNode* left, MathNode* right) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->type = type;
    new_node->data.op.left = left;
    new_node->data.op.right = right;
    return new_node;
}

double math_compute_graph(MathNode* graph) {
    if (graph->type == NODE_NUMBER) {
        return graph->data.value;
    } else if (graph->type == NODE_SUB) {
        return math_compute_graph(graph->data.op.left) - math_compute_graph(graph->data.op.right);
    } else if (graph->type == NODE_ADD) {
        return math_compute_graph(graph->data.op.left) + math_compute_graph(graph->data.op.right);
    } else if (graph->type == NODE_MUL) {
        return math_compute_graph(graph->data.op.left) * math_compute_graph(graph->data.op.right);
    } else if (graph->type == NODE_DIV) {
        return math_compute_graph(graph->data.op.left) * math_compute_graph(graph->data.op.right);
    } else if (graph->type == NODE_POW) {
        return pow(math_compute_graph(graph->data.op.left), math_compute_graph(graph->data.op.right));
    }
}
void table_free_graph(TableNode* graph) {
    if (graph->type == NODE_NUMBER) {
        math_free(graph);
    } else {
        math_free_graph(graph->data.op.left);
        math_free_graph(graph->data.op.right);
    }
}
