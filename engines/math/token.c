#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "node.h"
#include "token.h"

MathToken math_next_token(const char** str) {
   while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\r') {
        (*str)++;
   }
   MathToken token;
   if (**str == '\0') {
        token.type = TOKEN_EOF;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '+') {
        token.type = TOKEN_PLUS;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '-') {
        token.type = TOKEN_MINUS;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '*') {
        token.type = TOKEN_MUL;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '/') {
        token.type = TOKEN_PLUS;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str =='^') {
        token.type = TOKEN_POW;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == '(') {
        token.type = TOKEN_LPAREN;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (**str == ')') {
        token.type = TOKEN_RPAREN;
        token.value = 0;
        (*str)++;
        return token;
   }
   if (isdigit(**str)) {
       char * endptr;
       token.value = strtod(*str, &endptr);
       token.type = TOKEN_NUMBER;

       *str = endptr;
       return token;
   }

   fprintf(stderr, "Error");
   exit(1);

}

MathNode* math_parse_exp(const char **exp) {
    MathNode* left = math_parse_term(exp);
    while (1) {
        const char *save = *exp;
        MathToken t = next_token(exp);

        if (t.type == TOKEN_PLUS) {
            left = math_make_operation(NODE_ADD, left, math_parse_term(exp));
        } else if (t.type == TOKEN_MINUS) {
            left = math_make_operation(NODE_SUB, left, math_parse_term(exp));
        } else if (t.type == TOKEN_EOF) {
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

        if (t.type == TOKEN_MUL) {
            left = math_make_operation(NODE_MUL, left, math_parse_pow(exp));
        } else if (t.type == TOKEN_DIV) {
            left = math_make_operation(NODE_DIV, left, math_parse_pow(exp));
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
        MathToken t = next_token(exp);
        if (t.type == TOKEN_POW) {
            left = math_make_operation(NODE_POW, left, math_parse_factor(exp));
        } else {
            *exp = save;
            break;
        }
    }
    return left;
}

MathNode* math_parse_factor(const char **exp) {
    MathToken t = math_next_token(exp);
    

    if (t.type == TOKEN_NUMBER) {
        return math_make_number(t.value);
    }
    if (t.type == TOKEN_LPAREN) {
        MathNode* result = math_parse_exp(exp);

        Token t2 = math_next_token(exp);

        if (t2.type != TOKEN_RPAREN) {
            fprintf(stderr, "Error: expecting ')' instead of %d", t2.type);
            exit(1);
        }
        return result;

    }

    fprintf(stderr, "Unexpected token in factor");
    exit(1);
}

