#ifndef MATH_TOKEN_H
#define MATH_TOKEN_H

typedef enum {
    MATH_TOKEN_NUMBER,
    MATH_TOKEN_PLUS,
    MATH_TOKEN_MINUS,
    MATH_TOKEN_MUL,
    MATH_TOKEN_DIV,
    MATH_TOKEN_POW, 
    MATH_TOKEN_LPAREN,
    MATH_TOKEN_RPAREN,
    MATH_TOKEN_EOF
} MathTokenType;

typedef struct {
    MathTokenType type;
    double value; // specified only if type == TOKEN_NUMBER
} MathToken;
MathToken math_next_token(const char** str);
MathNode* math_parse_exp(const char **exp);
MathNode* math_parse_term(const char **exp);
MathNode* math_parse_pow(const char **exp);
MathNode* math_parse_factor(const char **exp);

#endif
