#ifndef NODE_H
#define NODE_H
#include "var.h"
typedef enum {
    NODE_VAR,
    NODE_NUMBER,
    NODE_ASSIGN,
    NODE_VIEW,
    NODE_WRITE
} TableNodeType;

typedef struct TableNode {
    TableNodeType type;
    union {
        struct {
            char name[MAX_VAR_NAME_LEN];
            struct TableNode* value;
        } assign;
        char name[MAX_VAR_NAME_LEN];
        double value;
    } data;
} TableNode;
void table_set_variable(const char* name, double value);
double table_get_variable(const char* name);
TableNode* table_make_var(char* name);
TableNode* table_make_assign(const char* name, double value);
TableNode* table_make_number(double value);
TableNode* table_make_view();
void table_print_all();
double table_compute_graph(TableNode* graph);
#endif
