#ifndef PIECES_H
#define PIECES_H

#include "board.h"
#include "player.h"
#include "util.h"

struct MoveList {
    int length;  // number of elements in a movelist
    struct Coordinate* coord;
};

// TODO: add destructor for MoveList

void initialize_movelist(struct MoveList *move_list);

void add_move(struct MoveList *move_list, int r, int c);

struct MoveList get_potential_moves(struct Coordinate from, char piece_type, struct Board *b);

bool is_king_in_check(struct Board *b, enum player_color pcolor);

#endif // PIECES_H
