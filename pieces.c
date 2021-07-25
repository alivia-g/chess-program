#include <assert.h>
#include <stdlib.h>

#include "board.h"
#include "pieces.h"
#include "util.h"

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

void initialize_movelist(struct MoveList *move_list) {
    move_list->length = 0;
}

void add_move(struct MoveList *move_list, int r, int c) {
    move_list->coord[move_list->length].r = r;
    move_list->coord[move_list->length].c = c;
    ++(move_list->length);
}

void get_bishop_moves(struct Coordinate from, struct Board *b, struct MoveList *to);
void get_rook_moves(struct Coordinate from, struct Board *b, struct MoveList *to);

/**
Parameters:
    from: coordinate of current piece
    piece_type: current piece type
    b: the game boards
Return:
    to: an array of all valid moves that current piece can go
**/
struct MoveList get_valid_moves(struct Coordinate from, char piece_type, struct Board *b) {
    struct MoveList to;
    initialize_movelist(&to);
    assert(to.length == 0);

    if (piece_type == BKNIGHT || piece_type == WKNIGHT) {
        to.coord = (struct Coordinate*) malloc(8 * sizeof(struct Coordinate));

        add_move(&to, from.r + 1, from.c - 2);
        add_move(&to, from.r + 1, from.c + 2);
        add_move(&to, from.r - 1, from.c - 2);
        add_move(&to, from.r - 1, from.c + 2);
        add_move(&to, from.r + 2, from.c - 1);
        add_move(&to, from.r + 2, from.c + 1);
        add_move(&to, from.r - 2, from.c - 1);
        add_move(&to, from.r - 2, from.c + 1);
    }
    if (piece_type == BQUEEN || piece_type == WQUEEN) {
        to.coord = (struct Coordinate*) malloc(27 * sizeof(struct Coordinate));
        get_rook_moves(from, b, &to);
        get_bishop_moves(from, b, &to);
    }
    if (piece_type == BKING || piece_type == WKING) {
        // TODO: implement castling
        to.coord = (struct Coordinate*) malloc(8 * sizeof(struct Coordinate));
        for (int r = from.r - 1; r <= from.r + 1; ++r) {
            for (int c = from.c - 1; c <= from.c + 1; ++c) {
                if ((r == from.r) && (c == from.c)) {
                    continue;
                } else {
                    add_move(&to, r, c);
                }
            }
        }
    }
    if (piece_type == BBISHOP || piece_type == WBISHOP) {
        to.coord = (struct Coordinate*) malloc(13 * sizeof(struct Coordinate));
        get_bishop_moves(from, b, &to);
    }
    if (piece_type == BROOK || piece_type == WROOK) {
        to.coord = (struct Coordinate*) malloc(14 * sizeof(struct Coordinate));
        get_rook_moves(from, b, &to);
    }
    if (piece_type == BPAWN) {
        // TODO: en passant
        to.coord = (struct Coordinate*) malloc(4 * sizeof(struct Coordinate));

        // black pawn moving down 1
        if (b->squares[from.r - 1][from.c] == EMPTY) {
            add_move(&to, from.r - 1, from.c);
            // check eligibility for initial 2-steps option
            if (from.r == 6 && b->squares[from.r - 2][from.c] == EMPTY) {
                add_move(&to, from.r - 2, from.c);
            }
        }
        // black pawn may eat the piece at its left-down diagonal
        if (from.r - 1 >= 0 && from.c - 1 >= 0 && b->squares[from.r - 1][from.c - 1] != EMPTY) {
            add_move(&to, from.r - 1, from.c - 1);
        }
        // black pawn may eat the piece at its right-down diagonal
        if (from.r - 1 >= 0 && from.c + 1 < 8 && b->squares[from.r - 1][from.c + 1] != EMPTY) {
            add_move(&to, from.r - 1, from.c + 1);
        }
    }
    if (piece_type == WPAWN) {
        // TODO: en passant
        to.coord = (struct Coordinate*) malloc(4 * sizeof(struct Coordinate));

        // white pawn moving up 1
        if (b->squares[from.r + 1][from.c] == EMPTY) {
            add_move(&to, from.r + 1, from.c);
            // check eligibility for initial 2-steps option
            if (from.r == 1 && b->squares[from.r + 2][from.c] == EMPTY) {
                add_move(&to, from.r + 2, from.c);
            }
        }
        // white pawn may eat the piece at its left-up diagonal
        if (from.r + 1 < 8 && from.c - 1 >= 0 && b->squares[from.r + 1][from.c - 1] != EMPTY) {
            add_move(&to, from.r + 1, from.c - 1);
        }
        // white pawn may eat the piece at its right-up diagonal
        if (from.r + 1 < 8 && from.c + 1 < 8 && b->squares[from.r + 1][from.c + 1] != EMPTY) {
            add_move(&to, from.r + 1, from.c + 1);
        }
    }
    if (piece_type == EMPTY) {
        to.length = 0;
        to.coord = NULL;
    } else {
        int marker = -1;  // marks the index of the right-most valid move in the "to" array
        for (int i= 0; i < to.length; ++i) {
            if (validate_coord(to.coord[i])) {
                ++marker;
                to.coord[marker] = to.coord[i];
            }
        }
        to.length = marker + 1;
    }
    return to;
}

// function to get an array of valid bishop moves
void get_bishop_moves(struct Coordinate from, struct Board *b, struct MoveList *to) {
    // bishop moving left-up diagonal
    for (int c = from.c - 1, r = from.r + 1; c >= 0, r < 8; --c, ++r) {
        add_move(&to, r, c);
        if (b->squares[r][c] != EMPTY) {
            break;
        }
    }
    // bishop moving right-down diagonal
    for (int c = from.c + 1, r = from.r - 1; c < 8, r >= 0; ++c, --r) {
        add_move(&to, r, c);
        if (b->squares[r][c] != EMPTY) {
            break;
        }
    }
    // bishop moving right-up diagonal
    for (int d = 1; d + max(from.c, from.r) < 8; ++d) {
        add_move(&to, from.r + d, from.c + d);
        if (b->squares[from.r + d][from.c + d] != EMPTY) {
            break;
        }
    }
    // bishop moving left-down diagonal
    for (int d = 1; max(from.c, from.r) - d >= 0; ++d) {
        add_move(&to, from.r - d, from.c - d);
        if (b->squares[from.r - d][from.c - d] != EMPTY) {
            break;
        }
    }
}

// function to get an array of valid rook moves
void get_rook_moves(struct Coordinate from, struct Board *b, struct MoveList *to) {
    // rook moving ups
    for (int r = from.r + 1; r < 8; ++r) {
        add_move(&to, r, from.c);
        if (b->squares[r][from.c] != EMPTY) {
            break;
        }
    }
    // rook moving down
    for (int r = from.r - 1; r >= 0; --r) {
        add_move(&to, r, from.c);
        if (b->squares[r][from.c] != EMPTY) {
            break;
        }
    }
    // rook moving right
    for (int c = from.c + 1; c < 8; ++c) {
        add_move(&to, from.r, c);
        if (b->squares[from.r][c] != EMPTY) {
            break;
        }
    }
    // rook moving left
    for (int c = from.c - 1; c >= 0; --c) {
        add_move(&to, from.r, c);
        if (b->squares[from.r][c] != EMPTY) {
            break;
        }
    }
}
