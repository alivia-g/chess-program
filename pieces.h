#ifndef PIECES_H
#define PIECES_H

struct MoveList {
    int length;
    struct Coordinate* coord;
};

// TODO: add destructor for MoveList

void initialize_movelist(struct MoveList *move_list);

void add_move(struct MoveList *move_list, int r, int c);

// struct MoveList get_valid_moves(struct Coordinate from, char piece_type, struct Board *b);


#endif // PIECES_H
