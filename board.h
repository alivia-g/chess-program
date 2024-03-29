#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include "player.h"
#include "util.h"

struct Board {
    char squares[8][8];
};

struct Move {
    struct Coordinate from;
    struct Coordinate to;
};

void clear(struct Board*);

struct Coordinate algebraic_to_coordinate(char*);

char* coordinate_to_algebraic(struct Coordinate);

char* stringify_move(struct Move);

char place_piece_with_algebraic_position(char, char*, struct Board*);

char place_piece_on_coordinate(char, struct Coordinate, struct Board*);

void initialize_default_board(struct Board*);

void initialize_custom_board(struct Board*);

void copy_board(struct Board*, struct Board*);

bool validate_coord(struct Coordinate);

enum player_color get_color(char);

void make_move(struct Board *b, struct Move move);

#endif // BOARD_H
