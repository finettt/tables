#ifndef VAR_H
#define VAR_H
#define MAX_VAR_NAME_LEN 256
#define MAX_VAR_C 256
#define MAX_ROWS 256
#define MAX_COLS 256
#define DEFAULT_ROWS 2
#define DEFAULT_COLS 2

typedef struct {
    char name[MAX_VAR_NAME_LEN];
    double matrix[MAX_ROWS][MAX_COLS];
    int rows, cols;
    int is_array; // 0-false, else - true
} Var;

extern Var variable_table[MAX_VAR_C];
extern int idx;
#endif
