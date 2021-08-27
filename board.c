#include <assert.h>
#include <stdio.h>

#include "board.h"
#include "util.h"
#include "player.h"

void clear(struct Board *b) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            b->squares[r][c] = EMPTY;
        }
    }
}

struct Coordinate algebraic_to_coordinate(char *pos) {
    assert(strlen(pos) == 2);
    struct Coordinate coord;
    coord.r = pos[1] - '1';
    coord.c = pos[0] - 'a';
    return coord;
};

char place_piece_with_algebraic_position(char piece, char *pos, struct Board *b) {
    struct Coordinate coord = algebraic_to_coordinate(pos);
    char old_piece = b->squares[coord.r][coord.c];
    // place piece on board
    b->squares[coord.r][coord.c] = piece;
    return old_piece;
}

char place_piece_on_coordinate(char piece, struct Coordinate coord, struct Board *b) {
    char old_piece = b->squares[coord.r][coord.c];
    // place piece on board
    b->squares[coord.r][coord.c] = piece;
    return old_piece;
}

void initialize_board(struct Board* b) {
    place_piece_with_algebraic_position(BROOK, "a8", b);
    place_piece_with_algebraic_position(BKNIGHT, "b8", b);
    place_piece_with_algebraic_position(BBISHOP, "c8", b);
    place_piece_with_algebraic_position(BQUEEN, "d8", b);
    place_piece_with_algebraic_position(BKING, "e8", b);
    place_piece_with_algebraic_position(BBISHOP, "f8", b);
    place_piece_with_algebraic_position(BKNIGHT, "g8", b);
    place_piece_with_algebraic_position(BROOK, "h8", b);

    place_piece_with_algebraic_position(WROOK, "a1", b);
    place_piece_with_algebraic_position(WKNIGHT, "b1", b);
    place_piece_with_algebraic_position(WBISHOP, "c1", b);
    place_piece_with_algebraic_position(WQUEEN, "d1", b);
    place_piece_with_algebraic_position(WKING, "e1", b);
    place_piece_with_algebraic_position(WBISHOP, "f1", b);
    place_piece_with_algebraic_position(WKNIGHT, "g1", b);
    place_piece_with_algebraic_position(WROOK, "h1", b);

    // place black pawns
    for (char f = 'a'; f <= 'h'; ++f) {
        char s[3] = "a2";
        s[0] = f;
        place_piece_with_algebraic_position(WPAWN, s, b);
    }
    // place white pawns
    for (char f = 'a'; f <= 'h'; ++f) {
        char s[3] = "a7";
        s[0] = f;
        place_piece_with_algebraic_position(BPAWN, s, b);
    }
}

// create a function to copy values from one board to another
void copy_board(struct Board* b1, struct Board* b2) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            b2->squares[r][c] = b1->squares[r][c];
        }
    }
}

// validate coordinate
bool validate_coord(struct Coordinate coord) {
    return (coord.r >= 0)&&(coord.r <= 7)&&(coord.c >= 0)&&(coord.c <= 7);
}

char get_color(char piece_type) {
    if (piece_type == EMPTY) {
        return none;
    } else if (('A' <= piece_type) && (piece_type <= 'Z')) {
        return white;
    } else if (('a' <= piece_type) && (piece_type <= 'z')) {
        return black;
    } else {
        return none;
    }
}
