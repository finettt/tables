#include <string.h>
#include <stdio.h>
#include "node.h"
#include <stdlib.h>
#include "var.h"

void table_set_variable(const char* name, int indices[2], int index_count, double value) {
    for (int i = 0; i < idx; i++) {
        if (strcmp(variable_table[i].name, name) == 0) {
            if (index_count == 0) {
                for (int r = 0; r < variable_table[i].rows; r++)
                    for (int c = 0; c < variable_table[i].cols; c++)
                        variable_table[i].matrix[r][c] = value;
            } else if (index_count == 1) {
                int row = indices[0];
                for (int c = 0; c < variable_table[i].cols; c++)
                    variable_table[i].matrix[row][c] = value;
            } else {
                variable_table[i].matrix[indices[0]][indices[1]] = value;
            }
            return;
        }
    }
    if (idx >= MAX_VAR_C) {
        fprintf(stderr, "Error: Variable table full\n");
        exit(1);
    }
    Var *v = &variable_table[idx];
    strncpy(v->name, name, MAX_VAR_NAME_LEN - 1);
    v->name[MAX_VAR_NAME_LEN - 1] = '\0';
    v->rows = DEFAULT_ROWS;
    v->cols = DEFAULT_COLS;
    v->is_array = 1;
    for (int r = 0; r < DEFAULT_ROWS; r++)
        for (int c = 0; c < DEFAULT_COLS; c++)
            v->matrix[r][c] = 0;

    if (index_count == 0) {
        for (int r = 0; r < v->rows; r++)
            for (int c = 0; c < v->cols; c++)
                v->matrix[r][c] = value;
    } else if (index_count == 1) {
        int row = indices[0];
        for (int c = 0; c < v->cols; c++)
            v->matrix[row][c] = value;
    } else {
        v->matrix[indices[0]][indices[1]] = value;
    }
    idx++;
}

double table_get_variable(const char* name, int indices[2], int index_count) {
    for (int i = 0; i < idx; i++) {
        if (strcmp(variable_table[i].name, name) == 0) {
            if (index_count == 0) {
                return variable_table[i].matrix[0][0];
            } else if (index_count == 1) {
                return variable_table[i].matrix[indices[0]][0];
            } else {
                return variable_table[i].matrix[indices[0]][indices[1]];
            }
        }
    }
    return -1;
}

TableNode* table_make_var(char* name, int indices[2], int index_count) {
    TableNode* new_node = (TableNode*)malloc(sizeof(TableNode));
    new_node->type = NODE_VAR;
    strncpy(new_node->data.var.name, name, MAX_VAR_NAME_LEN - 1);
    new_node->data.var.name[MAX_VAR_NAME_LEN - 1] = '\0';
    new_node->data.var.indices[0] = indices[0];
    new_node->data.var.indices[1] = indices[1];
    new_node->data.var.index_count = index_count;
    return new_node;
}

TableNode* table_make_assign(const char* name, int indices[2], int index_count, double value) {
    TableNode* new_node = (TableNode*)malloc(sizeof(TableNode));
    new_node->type = NODE_ASSIGN;
    strncpy(new_node->data.assign.name, name, MAX_VAR_NAME_LEN - 1);
    new_node->data.assign.name[MAX_VAR_NAME_LEN - 1] = '\0';
    new_node->data.assign.indices[0] = indices[0];
    new_node->data.assign.indices[1] = indices[1];
    new_node->data.assign.index_count = index_count;
    new_node->data.assign.value = table_make_number(value);
    return new_node;
}

TableNode* table_make_number(double value) {
    TableNode* new_node = (TableNode*)malloc(sizeof(TableNode));
    new_node->type = NODE_NUMBER;
    new_node->data.value = value;
    return new_node;
}

TableNode* table_make_view() {
    TableNode* new_node = (TableNode*)malloc(sizeof(TableNode));
    new_node->type = NODE_VIEW;
    new_node->data.value = 0;
    return new_node;
}

void table_print_all() {
    for (int i = 0; i < idx; i++) {
        printf("%s (%dx%d)\n", variable_table[i].name, variable_table[i].rows, variable_table[i].cols);
        for (int r = 0; r < variable_table[i].rows; r++) {
            for (int c = 0; c < variable_table[i].cols; c++) {
                if (c > 0) printf(" ");
                printf("%g", variable_table[i].matrix[r][c]);
            }
            printf("\n");
        }
    }
}

double table_compute_graph(TableNode* graph) {
    if (graph->type == NODE_NUMBER) {
        return graph->data.value;
    } else if (graph->type == NODE_VAR) {
        return table_get_variable(graph->data.var.name, graph->data.var.indices, graph->data.var.index_count);
    } else if (graph->type == NODE_ASSIGN) {
        table_set_variable(graph->data.assign.name, graph->data.assign.indices, graph->data.assign.index_count, graph->data.assign.value->data.value);
        return 0;
    } else if (graph->type == NODE_VIEW) {
        table_print_all();
        return 0;
    }
    return 0;
}
