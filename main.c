#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "node.h"
#include "token.h"

int main() {
    printf("Hello, world!\n");

    const char* code = "x EQ MATH 1+1";
    const char* ptr = code;

    TableNode* parsed_code = table_parse_exp(&ptr);
    table_compute_graph(parsed_code);
    free(parsed_code);

    const char* code2 = "a EQ MATH GET x+ 1";
    const char* ptr2 = code2;

    parsed_code = table_parse_exp(&ptr2);
    table_compute_graph(parsed_code);
    free(parsed_code);

    const char* code3 = "x$0$1 EQ 5";
    const char* ptr3 = code3;
    parsed_code = table_parse_exp(&ptr3);
    table_compute_graph(parsed_code);
    free(parsed_code);

    const char* code4 = "x$1$0 EQ 3";
    const char* ptr4 = code4;
    parsed_code = table_parse_exp(&ptr4);
    table_compute_graph(parsed_code);
    free(parsed_code);

    const char* code5 = "a EQ MATH GET x$0$1 + GET x$1$0";
    const char* ptr5 = code5;
    parsed_code = table_parse_exp(&ptr5);
    table_compute_graph(parsed_code);
    free(parsed_code);

    const char* code1 = "VIEW";
    const char* ptr1 = code1;

    parsed_code = table_parse_exp(&ptr1);
    table_compute_graph(parsed_code);
    free(parsed_code);


    return 0;
}
