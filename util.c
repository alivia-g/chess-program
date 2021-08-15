#include "util.h"

bool coords_equal(struct Coordinate c1, struct Coordinate c2) {
    if ((c1.r == c2.r) && (c1.c == c2.c)) {
       return true;
    }
    return false;
}
