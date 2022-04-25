#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "pieces.h"
#include "player.h"
#include "util.h"

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

void initialize_movelist(struct MoveList *move_list, int length) {
    move_list->length = length;
    if (length > 0) {
        move_list->coord = (struct Coordinate*) malloc(length * sizeof(struct Coordinate));
    }
}

void add_move(struct MoveList *move_list, int r, int c) {
    struct Coordinate coord;
    coord.r = r;
    coord.c = c;
    // only add moves that are on the board (in bounds)
    if (!validate_coord(coord)) { return; }
    move_list->coord[move_list->length].r = r;
    move_list->coord[move_list->length].c = c;
    ++(move_list->length);
}

void clear_movelist(struct MoveList *move_list) {
    free(move_list->coord);
    move_list->length = 0;
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
struct MoveList get_potential_moves(struct Coordinate from, struct Board *b) {
    char piece_type = b->squares[from.r][from.c];
    struct MoveList to;
    initialize_movelist(&to, 0);
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
    }

    return to;
}

// function to get an array of valid bishop moves
void get_bishop_moves(struct Coordinate from, struct Board *b, struct MoveList *to) {
    // bishop moving left-up diagonal
    for (int c = from.c - 1, r = from.r + 1; c >= 0 && r < 8; --c, ++r) {
        add_move(to, r, c);
        if (b->squares[r][c] != EMPTY) {
            break;
        }
    }
    // bishop moving right-down diagonal
    for (int c = from.c + 1, r = from.r - 1; c < 8 && r >= 0; ++c, --r) {
        add_move(to, r, c);
        if (b->squares[r][c] != EMPTY) {
            break;
        }
    }
    // bishop moving right-up diagonal
    for (int d = 1; d + max(from.c, from.r) < 8; ++d) {
        add_move(to, from.r + d, from.c + d);
        if (b->squares[from.r + d][from.c + d] != EMPTY) {
            break;
        }
    }
    // bishop moving left-down diagonal
    for (int d = 1; min(from.c, from.r) - d >= 0; ++d) {
        add_move(to, from.r - d, from.c - d);
        if (b->squares[from.r - d][from.c - d] != EMPTY) {
            break;
        }
    }
}

// function to get an array of valid rook moves
void get_rook_moves(struct Coordinate from, struct Board *b, struct MoveList *to) {
    // rook moving ups
    for (int r = from.r + 1; r < 8; ++r) {
        add_move(to, r, from.c);
        if (b->squares[r][from.c] != EMPTY) {
            break;
        }
    }
    // rook moving down
    for (int r = from.r - 1; r >= 0; --r) {
        add_move(to, r, from.c);
        if (b->squares[r][from.c] != EMPTY) {
            break;
        }
    }
    // rook moving right
    for (int c = from.c + 1; c < 8; ++c) {
        add_move(to, from.r, c);
        if (b->squares[from.r][c] != EMPTY) {
            break;
        }
    }
    // rook moving left
    for (int c = from.c - 1; c >= 0; --c) {
        add_move(to, from.r, c);
        if (b->squares[from.r][c] != EMPTY) {
            break;
        }
    }
}

// check if a player's King is under check
// TODO: keep track of each piece that is under attack
bool is_king_in_check(struct Board *b, enum player_color pcolor) {
    char king_type = 0;
    assert((king_type == black) || (king_type == white));
    if (pcolor == black) { king_type = 'k'; }
    else if (pcolor == white) { king_type = 'K'; }

    struct Coordinate king_coord;
    king_coord.r = -1;  // initialization is important
    king_coord.c = -1;

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (b->squares[r][c] == king_type) {
                king_coord.r = r;
                king_coord.c = c;
                break;
            }
        }
    }

    // if no King present on board, return false directly
    if ((king_coord.r < 0) || (king_coord.c < 0)) { return false; }

    // iterate through the board pieces
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (get_color(b->squares[r][c]) != pcolor) {
                // get valid moves of current piece
                struct Coordinate coord;
                coord.r = r;
                coord.c = c;

                struct MoveList valid_moves = get_potential_moves(coord, b);

                // check if the coordinate of the pcolor's King is contained in valid_moves
                for (int i = 0; i < valid_moves.length; ++i) {
                    if (coords_equal(king_coord, valid_moves.coord[i])) { return true; }  // King is under check
                }
            }
        }
    }
    return false;  // King is not under check
}

// helper function to check if a potential move is valid
bool is_move_valid(struct Coordinate from, struct Coordinate to, struct Board *b, enum player_color current_player) {
    // boundary check
    if (!validate_coord(to)) { return false; }

    enum player_color piece_color = get_color(b->squares[from.r][from.c]);
    if (current_player != piece_color) { return false; }

    char piece_type = b->squares[from.r][from.c];
    // a piece cannot capture pieces of the same color
    if (get_color(b->squares[to.r][to.c]) == get_color(piece_type)) { return false; }

    // move the piece to a potential position
    char captured_piece = place_piece_on_coordinate(piece_type, to, b);
    // remove the piece at "from" position
    place_piece_on_coordinate(EMPTY, from, b);

    bool valid = true;
    // check if the King would be in check after moving the piece to the potential position
    if (is_king_in_check(b, get_color(piece_type))) { valid = false; }

    // restore the captured piece back to its original position
    place_piece_on_coordinate(captured_piece, to, b);
    // restore the piece back to its original position
    place_piece_on_coordinate(piece_type, from, b);

    return valid;
}

// gets a list of valid moves for a piece at a coordinate on the board
//struct MoveList get_valid_moves(struct Coordinate from, struct Board *b, enum player_color pcolor) {
//    struct MoveList moves = get_potential_moves(from, b);
//
//    char piece_type = b->squares[from.r][from.c];
//    if (piece_type == EMPTY) {
//        moves.length = 0;
//        moves.coord = NULL;
//        return moves;
//    }
//
//    // filter potential moves array to remove invalid moves
//    int ptr = 0;  // marks the index of right-most valid move in moves array
//    for (int i = 0; i < moves.length; ++i) {
//        if (is_move_valid(from, moves.coord[i], b, pcolor)) {
//            moves.coord[ptr] = moves.coord[i];
//            ++ptr;
//        }
//    }
//    moves.length = ptr;
//    return moves;
//}


struct MoveList get_valid_moves(struct Coordinate from, struct Board *b, enum player_color pcolor) {
    struct MoveList moves = get_potential_moves(from, b);

    char piece_type = b->squares[from.r][from.c];
    if (piece_type == EMPTY) {
        moves.length = 0;
        moves.coord = NULL;
        return moves;
    }

    // filter potential moves array to remove invalid moves
    int ptr = 0;  // marks the index of right-most valid move in moves array
    for (int i = 0; i < moves.length; ++i) {
        if (is_move_valid(from, moves.coord[i], b, pcolor)) {
            moves.coord[ptr] = moves.coord[i];
            ++ptr;
        }
    }
    moves.length = ptr;
    return moves;
}


// source: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
// randomly shuffle the movelist
void shuffle_movelist(struct MoveList *move_list) {
    time_t t;
    srand((unsigned) time(&t));  // seed
    for (int i = move_list->length - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        // swap ith and jth move
        struct Coordinate temp = move_list->coord[i];
        move_list->coord[i] = move_list->coord[j];
        move_list->coord[j] = temp;
    }
}

// returns a randomly ordered list of valid moves
struct MoveList get_shuffled_valid_moves(struct Coordinate from, struct Board *b, enum player_color pcolor) {
    struct MoveList move_list = get_valid_moves(from, b, pcolor);
    shuffle_movelist(&move_list);

    return move_list;
}

// check if a player has any valid moves remaining on board
bool player_has_valid_moves(struct Board *b, enum player_color pcolor) {
    struct Coordinate coord;
    for (int r = 0; r < 8; ++r) {
        coord.r = r;
        for (int c = 0; c < 8; ++c) {
            coord.c = c;
            if (get_color(b->squares[r][c]) == pcolor
                 && get_valid_moves(coord, b, pcolor).length >= 1) {
                return true;
            }
        }
    }
    return false;  // player has no more valid moves
}

/**
* check for checkmate
* checkmate conditions:
* 1. player's King is under check &&
* 2. player has no valid moves on the board
**/
bool is_player_under_check_mated(struct Board *b, enum player_color pcolor) {
    return !player_has_valid_moves(b, pcolor);
}

/**
* check for stalemate
* stalemate conditions:
* 1. player's King is NOT in check &&
* 2. player has no valid moves on the board
**/
bool is_unchecked_player_stalemated(struct Board *b, enum player_color pcolor) {
    return !player_has_valid_moves(b, pcolor);
}

/**
* Following the standard valuations of pieces' point value assignments.
* queen: 9
* rook: 5
* knight: 3
* bishop: 3
* pawn: 1
* Note: king is given a value (i.e. 1000) larger than the sum of all the pieces on the board without causing overflow
**/
int get_piece_value(char piece) {
    switch (piece) {
        case 'N':
        case 'n':
            return 3;
        case 'Q':
        case 'q':
            return 9;
        case 'K':
        case 'k':
            return 1000;
        case 'B':
        case 'b':
            return 3;
        case 'R':
        case 'r':
            return 5;
        case 'P':
        case 'p':
            return 1;
        default:
            return 0;
    }
}
