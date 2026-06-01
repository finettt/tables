#ifndef VAR_H
#define VAR_H
#define MAX_VAR_NAME_LEN 256
#define MAX_VAR_C 256

typedef struct {
    char name[MAX_VAR_NAME_LEN];
    double value;
} Var;

extern Var variable_table[MAX_VAR_C];
extern int idx;
#endif
