#ifndef UTILS_H
#define UTILS_H

/* Parse "$r$c" suffix string into indices array.
 * Returns number of indices filled (0, 1, or 2). */
int parse_indices(const char *suffix, int *indices);

#endif
