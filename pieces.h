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

struct MoveList get_valid_moves(struct Coordinate from, struct Board *b);

bool is_king_in_check(struct Board *b, enum player_color pcolor);

bool is_player_under_check_mated();

bool is_unchecked_player_stalemated();

#endif // PIECES_H
