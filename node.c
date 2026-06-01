#include <string.h>
#include <stdio.h>
#include "node.h"
#include <stdlib.h>
#include "var.h"

void table_set_variable(const char* name, double value) {
    for (int i = 0; i < idx; i++) {
        if (strcmp(variable_table[i].name, name) == 0) {
            variable_table[i].value = value; 
            return;
        }
    }
    if (idx >= MAX_VAR_C) {
        fprintf(stderr, "Error: Variable table full\n");
        exit(1);
    }
    strncpy(variable_table[idx].name, name, MAX_VAR_NAME_LEN - 1);
    variable_table[idx].name[MAX_VAR_NAME_LEN - 1] = '\0';
    variable_table[idx].value = value;
    idx++;
}
double table_get_variable(const char* name) {
    for (int i = 0; i < idx; i++) {
        if (strcmp(variable_table[i].name, name) == 0) {
            return variable_table[i].value;
        }
    }
    return -1;
}
TableNode* table_make_var(char* name) {
    TableNode* new_node = (TableNode*)malloc(sizeof(TableNode));
    new_node->type = NODE_VAR;
    strncpy(new_node->data.name, name, MAX_VAR_NAME_LEN - 1);
    new_node->data.name[MAX_VAR_NAME_LEN - 1] = '\0';
    // set_variable(name, 0);
    return new_node;
}

TableNode* table_make_assign(const char* name, double value) {
    TableNode* new_node = (TableNode*)malloc(sizeof(TableNode));
    new_node->type = NODE_ASSIGN;
    strncpy(new_node->data.assign.name, name, MAX_VAR_NAME_LEN - 1);
    new_node->data.assign.name[MAX_VAR_NAME_LEN - 1] = '\0';
    new_node->data.assign.value = table_make_number(value);
    // set_variable(name, value);
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
        printf("%s\n", variable_table[i].name);
        printf("%f\n", variable_table[i].value);
    }
}

double table_compute_graph(TableNode* graph) {
    if (graph->type == NODE_NUMBER) {
        return graph->data.value;
    } else if (graph->type == NODE_VAR) {
        return table_get_variable(graph->data.name);
    } else if (graph->type == NODE_ASSIGN) {
        table_set_variable(graph->data.assign.name, graph->data.assign.value->data.value); //holy shit! we extract double from deep dark!
        return 0;
    } else if (graph->type == NODE_VIEW) {
        table_print_all();
        return 0;
    }
}   
