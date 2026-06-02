#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "node.h"
#include "../../token.h"
#include "../../node.h"
#include "token.h"
#include <stddef.h>
#include <string.h>

#define GET_OP "GET"

MathToken math_next_token(const char** str) {
   while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\r') {
        (*str)++;
   }
   MathToken token;
   if (**str == '\0') {
        token.type = MATH_TOKEN_EOF;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '+') {
        token.type = MATH_TOKEN_PLUS;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '-') {
        token.type = MATH_TOKEN_MINUS;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '*') {
        token.type = MATH_TOKEN_MUL;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '/') {
        token.type = MATH_TOKEN_PLUS;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str =='^') {
        token.type = MATH_TOKEN_POW;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '(') {
        token.type = MATH_TOKEN_LPAREN;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == ')') {
        token.type = MATH_TOKEN_RPAREN;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (isdigit(**str)) {
       char * endptr;
       token.value = strtod(*str, &endptr);
       token.type = MATH_TOKEN_NUMBER;

       *str = endptr;
       return token;
   }
   if (strncmp(*str, GET_OP, sizeof(GET_OP)) == 0 && !isalnum((*str)[sizeof(GET_OP)])) {
        token.type = MATH_TOKEN_GET;
        token.value = 0;
        *str += 3;
        return token;
   }
   if (isalpha(**str) || **str == '_'){
        token.type = MATH_TOKEN_VAR;
        token.value = 0;
        char* start = *str;
        while (isalnum(**str) || **str == '_') {
            (*str)++;
        }
        ptrdiff_t length = *str - start;

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
   fprintf(stderr, "Error");
   exit(1);

}

MathNode* math_parse_exp(const char **exp) {
    MathNode* left = math_parse_term(exp);
    while (1) {
        const char *save = *exp;
        MathToken t = math_next_token(exp);

        if (t.type == MATH_TOKEN_PLUS) {
            left = math_make_operation(MATH_NODE_ADD, left, math_parse_term(exp));
        } else if (t.type == MATH_TOKEN_MINUS) {
            left = math_make_operation(MATH_NODE_SUB, left, math_parse_term(exp));
        } else if (t.type == MATH_TOKEN_EOF) {
            *exp = save;
            break;
        } else {
            *exp = save;
            break;
        }
    }
    return left;
}

MathNode* math_parse_term(const char **exp) {
    MathNode* left = math_parse_pow(exp);
    while (1) {
        const char *save = *exp;
        MathToken t = math_next_token(exp);

        if (t.type == MATH_TOKEN_MUL) {
            left = math_make_operation(MATH_NODE_MUL, left, math_parse_pow(exp));
        } else if (t.type == MATH_TOKEN_DIV) {
            left = math_make_operation(MATH_NODE_DIV, left, math_parse_pow(exp));
        } else {
            *exp = save;
            break;
        }
    }
    return left;
}

MathNode* math_parse_pow(const char **exp) {
    MathNode* left = math_parse_factor(exp);
    while (1) {
        const char *save = *exp;
        MathToken t = math_next_token(exp);
        if (t.type == MATH_TOKEN_POW) {
            left = math_make_operation(MATH_NODE_POW, left, math_parse_factor(exp));
        } else {
            *exp = save;
            break;
        }
    }
    return left;
}

MathNode* math_parse_factor(const char **exp) {
    MathToken t = math_next_token(exp);
    

    if (t.type == MATH_TOKEN_NUMBER) {
        return math_make_number(t.value);
    }
    if(t.type == MATH_TOKEN_GET) {
            TableToken t2 = table_next_token(exp);
            if (t2.type == MATH_TOKEN_VAR) {
                double value = table_get_variable(t2.name);
                return math_make_number(value);
            }
            fprintf(stderr, "Error: Expected variable after GET");
            exit(1);
    }
    if (t.type == MATH_TOKEN_LPAREN) {
        MathNode* result = math_parse_exp(exp);

        MathToken t2 = math_next_token(exp);

        if (t2.type != MATH_TOKEN_RPAREN) {
            fprintf(stderr, "Error: expecting ')' instead of %d", t2.type);
            exit(1);
        }
        return result;

    }

    fprintf(stderr, "Unexpected token in factor");
    exit(1);
}

