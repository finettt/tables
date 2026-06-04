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
            int indices[2];
            int index_count;
        } var;
        struct {
            char name[MAX_VAR_NAME_LEN];
            int indices[2];
            int index_count;
            struct TableNode* value;
        } assign;
        double value;
    } data;
} TableNode;
void table_set_variable(const char* name, int indices[2], int index_count, double value);
double table_get_variable(const char* name, int indices[2], int index_count);
TableNode* table_make_var(char* name, int indices[2], int index_count);
TableNode* table_make_assign(const char* name, int indices[2], int index_count, double value);
TableNode* table_make_number(double value);
TableNode* table_make_view();
void table_print_all();
double table_compute_graph(TableNode* graph);
#endif
