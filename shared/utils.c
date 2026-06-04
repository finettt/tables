#include <stdlib.h>
#include <string.h>
#include "utils.h"

int parse_indices(const char *suffix, int *indices) {
    int count = 0;
    const char *p = suffix;

    while (*p && count < 2) {
        if (*p == '$') {
            p++;
            indices[count++] = (int)atol(p);
            while (*p >= '0' && *p <= '9') p++;
        } else {
            break;
        }
    }
    return count;
}
