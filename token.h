#ifndef TOKEN_H
#define TOKEN_H
#include "node.h"
typedef enum {
    TOKEN_VAR,
    TOKEN_EQ,
    TOKEN_VIEW,
    TOKEN_EOF,
    TOKEN_GET,
    TOKEN_MATH,
    TOKEN_NUMBER
} TableTokenType;

typedef struct {
    TableTokenType type;
    double value;
    char* name;
} TableToken;

TableToken table_next_token(const char **exp);
TableNode* table_parse_exp(const char **exp);
TableNode* table_parse_factor(const char **exp);
#endif
