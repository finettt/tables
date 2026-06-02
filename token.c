#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "token.h"
#include "node.h"
#include "engines/math/node.h"
#include "engines/math/token.h"

static const char VIEW_OP[] = "VIEW";
static const char EQ_OP[] = "EQ";
static const char GET_OP[] = "GET";
static const char MATH_OP[] = "MATH";

TableToken table_next_token(const char **exp) {
    while (**exp == ' ' || **exp == '\t' || **exp == '\r' || **exp == '\n')
    {
        (*exp)++;
    }
    TableToken token;
    if (**exp == '\0') {
        token.type = TOKEN_EOF;
        token.value = 0;
        return token;
    }
    if (strncmp(*exp, VIEW_OP, sizeof(VIEW_OP)-1) == 0) { 
        token.type = TOKEN_VIEW;
        token.value = 0;
        *exp += 4;
        return token;
    }
    if (strncmp(*exp, EQ_OP, sizeof(EQ_OP)-1) == 0) { 
        token.type = TOKEN_EQ;
        token.value = 0;
        *exp += 2;
        return token;
    }
    if (strncmp(*exp, GET_OP, sizeof(GET_OP)-1) == 0) { 
        token.type = TOKEN_GET;
        token.value = 0;
        *exp += 3;
        return token;
    }
    if (strncmp(*exp, MATH_OP, sizeof(MATH_OP)-1) == 0) { 
        token.type = TOKEN_MATH;
        token.value = 0;
        *exp += 4;
        return token;
    }
    if (isdigit(**exp) || (**exp == '.' && isdigit((*exp)[1]))) {
        token.type = TOKEN_NUMBER;
        token.value = atof(*exp);
        while (isdigit(**exp) || **exp == '.') {
            (*exp)++;
        }
        return token;
    }
    if (isalpha(**exp) || **exp == '_'){
        token.type = TOKEN_VAR;
        token.value = 0;
        char* start = *exp;
        while (isalnum(**exp) || **exp == '_') {
            (*exp)++;
        }
        ptrdiff_t length = *exp - start;

        char* var_name = (char*)malloc((length + 1) * sizeof(char));
        if (var_name == NULL){
            fprintf(stderr, "Error while allocating memory");
            exit(1);
        }
        strncpy(var_name, start, length);
        var_name[length] = '\0';
        token.name = var_name;
        return token;
    } 
    fprintf(stderr, "Unexpected character: %c\n", **exp);
    exit(1);
}

TableNode* table_parse_exp(const char **exp) {
    TableNode* left = table_parse_factor(exp);
    while (1) {
        const char *save = *exp;
        TableToken t = table_next_token(exp);
        
        if (t.type == TOKEN_EQ) {
            TableNode* factor = table_parse_factor(exp);
            switch (factor->type) {
                case NODE_NUMBER:
                    break;
                default:
                    fprintf(stderr, "Expected a number or variable after EQ token");
                    exit(1);
            }
            left = table_make_assign(left->data.name, factor->data.value);
            return left;
        } 
        if(t.type == TOKEN_EOF) {
            *exp = save;
            break;
        } else {
            *exp = save;
            break;
        }
    }
    return left;
}
TableNode* table_parse_factor(const char **exp) {
        TableToken t = table_next_token(exp);
        if (t.type == TOKEN_VAR) {
            return table_make_var(t.name);
        }
        if(t.type == TOKEN_GET) {
            TableToken t2 = table_next_token(exp);
            if (t2.type == TOKEN_VAR) {
                double value = table_get_variable(t2.name);
                return table_make_number(value);
            }
            fprintf(stderr, "Error: Expected variable after GET");
            exit(1);
        }
        if(t.type == TOKEN_MATH) {
            MathNode* parsed_math = math_parse_exp(exp);
            double result = math_compute_graph(parsed_math);
            math_free_graph(parsed_math);
            return table_make_number(result); 
        }
        if (t.type == TOKEN_NUMBER) {
            return table_make_number(t.value);
        }
        if (t.type == TOKEN_VIEW) {
            return table_make_view();
        }
        fprintf(stderr, "Error: Unxpected token in factor layer!"); 
        exit(1);
}
