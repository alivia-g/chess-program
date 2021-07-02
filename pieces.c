#include "pieces.h"

struct MoveList {
    int length;
    Coordinate[] coord;
    MoveList() {  // constructor
        length = 0;
    }
    // TODO: add destructor
    void add_move(int r, int c) {
        coord[length].r = r;
        coord[length].c = c;
        ++length;
    }
};

/**
Parameters:
    from: coordinate of current piece
    piece_type: current piece type
    b: the game boards
Return:
    to: an array of all valid moves that current piece can go
**/
struct MoveList get_valid_moves(struct Coordinate from, char piece_type, Board *b) {
    struct MoveList to;

    switch (piece_type) {
        case BKNIGHT:
        case WKNIGHT:
        {
            to.coord = (Coordinate*) malloc(8 * sizeof(Coordinate));

            to.coord.add_move(from.r + 1, from.c - 2);
            to.coord.add_move(from.r + 1, from c + 2);
            to.coord.add_move(from.r - 1, from.c - 2);
            to.coord.add_move(from.r - 1, from.c + 2);
            to.coord.add_move(from.r + 2, from.c - 1);
            to.coord.add_move(from.r + 2, from.c + 1);
            to.coord.add_move(from.r - 2, from.c - 1);
            to.coord.add_move(from.r - 2, from.c + 1);

            //to.coord[0].r = from.r + 1;
            //to.coord[0].c = from.c - 2;

            //to.coord[1].r = from.r + 1;
            //to.coord[1].c = from.c + 2;

            //to.coord[2].r = from.r - 1;
            //to.coord[2].c = from.c - 2;

            //to.coord[3].r = from.r - 1;
            //to.coord[3].c = from.c + 2;

            //to.coord[4].r = from.r + 2;
            //to.coord[4].c = from.c - 1;

            //to.coord[5].r = from.r + 2;
            //to.coord[5].c = from.c + 1;

            //to.coord[6].r = from.r - 2;
            //to.coord[6].c = from.c - 1;

            //to.coord[7].r = from.r - 2;
            //to.coord[7].c = from.c + 1;
            break;
        }
        case BQUEEN:
        case WQUEEN:
        {
            to.coord = (Coordinate*) malloc(8 * sizeof(Coordinate));

            break;
        }
        case BKING:
        case WKING:
        {
            // TODO: implement castling
            to.coord = (Coordinate*) malloc(8 * sizeof(Coordinate));
            int i = 0;  // index counter for "to" array
            for (int r = from.r - 1; r <= from.r + 1; ++r) {
                for (int c = from.c - 1; c <= from.c + 1; ++c) {
                    if ((r == from.r)&&(c == from.c)) {
                        continue;
                    } else {
                        to.coord[i].r = r;
                        to.coord[i].c = c;
                        ++i;
                    }
                }
            }
            break;
        }
        case BBISHOP:
        case WBISHOP:
        {
            to.coord = (Coordinate*) malloc(13 * sizeof(Coordinate));
            int i = 0;  // index counter for "to" array
            // bishop moving left-up diagonal
            for (int c = from.c - 1, r = from.r + 1; c >= 0, r < 8; --c, ++r) {
                to.coord[i].r = r;
                to.coord[i].c = c;
                ++i;
                if (b.squares[r][c] != EMPTY) {
                    break;
                }
            }
            // bishop moving right-down diagonal
            for (int c = from.c + 1, r = from.r - 1; c < 8, r >= 0; ++c, --r) {
                to.coord[i].r = r;
                to.coord[i].c = c;
                ++i;
                if (b.squares[r][c] != EMPTY) {
                    break;
                }
            }
            // bishop moving right-up diagonal
            for (int d = 1; d + max(from.c, from.r) < 8; ++d) {
                to.coord[i].r = from.r + d;
                to.coord[i].c = from.c + d;
                ++i;
                if (b.squares[from.r + d][from.c + d] != EMPTY) {
                    break;
                }
            }
            // bishop moving left-down diagonal
            for (int d = 1; max(from.c, from.r) - d >= 0; ++d) {
                to.coord[i].r = from.r - d;
                to.coord[i].c = from.c - d;
                ++i;
                if (b.squares[from.r - d][from.c - d] != EMPTY) {
                    break;
                }
            }
            break;
        }
        case BROOK:
        case WROOK:
        {
            to.coord = (Coordinate*) malloc(14 * sizeof(Coordinate));
            int i = 0;  // index counter for "to" array
            // rook moving ups
            for (int r = from.r + 1; r < 8; ++r) {
                to.coord[i].r = r;
                to.coord[i].c = from.c;
                ++i;
                if (b.squares[r][from.c] != EMPTY) {
                    break;
                }
            }
            // rook moving down
            for (int r = from.r - 1; r >= 0; --r) {
                to.coord[i].r = r;
                to.coord[i].c = from.c;
                ++i;
                if (b.squares[r][from.c] != EMPTY) {
                    break;
                }
            }
            // rook moving right
            for (int c = from.c + 1; c < 8; ++c) {
                to.coord[i].r = from.r;
                to.coord[i].c = c;
                ++i;
                if (b.squares[from.r][c] != EMPTY) {
                    break;
                }
            }
            // rook moving left
            for (int c = from.c - 1; c >= 0; --c) {
                to.coord[i].r = from.r;
                to.coord[i].c = c;
                ++i;
                if (b.squares[from.r][c] != EMPTY) {
                    break;
                }
            }
            break;
        }
        case BPAWN: {
            // TODO: en passant
            to.coord = (Coordinate*) malloc(4 * sizeof(Coordinate));
            int i = 0;  // index counter for "to" array
            // black pawn moving down 1
            if (b.squares[from.r - 1][from.c] == EMPTY) {
                to.coord[i].r = from.r - 1;
                to.coord[i].c = from.c;
                ++i;
                // check eligibility fro initial 2-steps option
                if (from.r == 6 && b.squares[from.r - 2][from.c] == EMPTY) {
                    to.coord[i].r = from.r - 2;
                    to.coord[i].c = from.c;
                    ++i;
                }
            }
            // black pawn may eat the piece at its left-down diagonal
            if (from.r - 1 >= 0 && from.c - 1 >= 0 && b.squares[from.r - 1][from.c - 1] != EMPTY) {
                to.coord[i].r = from.r - 1;
                to.coord[i].c = from.c - 1;
                ++i;
            }
            // black pawn may eat the piece at its right-down diagonal
            if (from.r - 1 >= 0 && from.c + 1 < 8 && b.squares[from.r - 1][from.c + 1] != EMPTY) {
                to.coord[i].r = from.r - 1;
                to.coord[i].c = from.c + 1;
                ++i;
            }
            break;
        }
        case WPAWN:
            // TODO: en passant
            to.coord = (Coordinate*) malloc(4 * sizeof(Coordinate));
            int i = 0;  // index counter for "to" array
            // white pawn moving up 1
            if (b.squares[from.r + 1][from.c] == EMPTY)
                to.coord[i].r = from.r + 1;
                to.coord[i].c = from.c;
                ++i;
                // check eligibility for initial 2-steps option
                if (from.r == 1 && b.squares[from.r + 2][from.c] == EMPTY) {
                    to.coord[i].r = from.r + 2;
                    to.coord[i].c = from.c;
                    ++i;
                }
            }
            // white pawn may eat the piece at its left-up diagonal
            if (from.r + 1 < 8 && from.c - 1 >= 0 && b.squares[from.r + 1][from.c - 1] != EMPTY) {
                to.coord[i].r = from.r + 1;
                to.coord[i].c = from.c - 1;
                ++i;
            }
            // white pawn may eat the piece at its right-up diagonal
            if (from.r + 1 < 8 && from.c + 1 < 8 && b.squares[from.r + 1][from.c + 1] != EMPTY) {
                to.coord[i].r = from.r + 1;
                to.coord[i].c = from.c + 1;
                ++i;
            }
            break;
        }
        case EMPTY:
        default: {
            to.length = 0;
            to.coord = NULL;
        }
    }

    return moves;
}

