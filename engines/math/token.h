#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_POW, 
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF
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
