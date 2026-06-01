#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "node.h"
#include "token.h"

int main() {
    printf("Hello, world!\n");

    const char* code = "x EQ 1";
    const char* ptr = code;
    
    TableNode* parsed_code = table_parse_exp(&ptr);
    table_compute_graph(parsed_code);

    const char* code2 = "a EQ GET x";
    const char* ptr2 = code2;
    
    parsed_code = table_parse_exp(&ptr2);
    table_compute_graph(parsed_code);


    const char* code1 = "VIEW";
    const char* ptr1 = code1;
    
    parsed_code = table_parse_exp(&ptr1);
    table_compute_graph(parsed_code);
    free(parsed_code);


    return 0;
}
