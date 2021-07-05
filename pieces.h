#ifndef PIECES_H
#define PIECES_H

const char EMPTY = ' ';

// white pieces
const char WKNIGHT = 'N';
const char WQUEEN = 'Q';
const char WKING = 'K';
const char WBISHOP = 'B';
const char WROOK = 'R';
const char WPAWN = 'P';
// black pieces
const char BKNIGHT = 'n';
const char BQUEEN = 'q';
const char BKING = 'k';
const char BBISHOP = 'b';
const char BROOK = 'r';
const char BPAWN = 'p';

struct Coordinate {
    int r, c;
};

struct MoveList {
    int length;
    struct Coordinate* coord;
};

// TODO: add destructor for MoveList

void initialize_movelist(struct MoveList *move_list) {
    move_list->length = 0;
}

void add_move(struct MoveList *move_list, int r, int c) {
    move_list->coord[move_list->length].r = r;
    move_list->coord[move_list->length].c = c;
    ++(move_list->length);
}

// struct MoveList get_valid_moves(struct Coordinate from, char piece_type, struct Board *b);


#endif // PIECES_H
