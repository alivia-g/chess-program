#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include "player.h"

struct Board {
    char squares[8][8];
};

void clear(struct Board*);

struct Coordinate algebraic_to_coordinate(char*);

char place_piece_with_algebraic_position(char, char*, struct Board*);

char place_piece_on_coordinate(char, struct Coordinate, struct Board*);

void initialize_board(struct Board*);

void copy_board(struct Board*, struct Board*);

bool validate_coord(struct Coordinate);

enum player_color get_color(char);

#endif // BOARD_H
