#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdio.h>

static const char EMPTY = ' ';

// white pieces
static const char WKNIGHT = 'N';
static const char WQUEEN = 'Q';
static const char WKING = 'K';
static const char WBISHOP = 'B';
static const char WROOK = 'R';
static const char WPAWN = 'P';
// black pieces
static const char BKNIGHT = 'n';
static const char BQUEEN = 'q';
static const char BKING = 'k';
static const char BBISHOP = 'b';
static const char BROOK = 'r';
static const char BPAWN = 'p';

struct Coordinate {
    int r, c;
};

bool coords_equal(struct Coordinate, struct Coordinate);

void open_log_file(FILE** file_ptr, char *file_name);

#endif  // UTIL_H
