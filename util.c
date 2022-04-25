#include "util.h"

#include <stdio.h>

bool coords_equal(struct Coordinate c1, struct Coordinate c2) {
    if ((c1.r == c2.r) && (c1.c == c2.c)) {
       return true;
    }
    return false;
}

void open_log_file(FILE** file_ptr, char *file_name) {
    if (*file_ptr == 0) {
        *file_ptr = fopen(file_name, "w");
    }
}
