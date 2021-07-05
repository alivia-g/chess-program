#ifndef BOARD_H
#define BOARD_H

#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "pieces.h"

struct Board {
    char squares[8][8];
};

void clear(struct Board*);

struct Coordinate algebraic_to_coordinate(char*);

char place_piece(char, char*, struct Board*);

void initialize_board(struct Board*);

void copy_board(struct Board*, struct Board*);

bool validate_coord(struct Coordinate);

#endif // BOARD_H
