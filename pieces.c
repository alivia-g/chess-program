#include "pieces.h"

struct MoveList {
    int length;
    Coordinate[] coord;
};

/**
Parameters:
    coord: coordinate of current piece
    piece_type: current piece type
Return:
    moves: an array of all valid moves that current piece can make
**/
struct MoveList get_valid_moves(struct Coordinate coord, char piece_type, Board *b) {
    struct MoveList moves;

    switch (piece_type) {
        case BKNIGHT:
        case WKNIGHT:
        {
            moves.coord = (Coordinate*) malloc(8 * sizeof(Coordinate));

            moves.coord[0].r = coord.r + 1
            moves.coord[0].c = coord.c - 2

            moves.coord[1].r = coord.r + 1
            moves.coord[1].c = coord.c + 2

            moves.coord[2].r = coord.r - 1
            moves.coord[2].c = coord.c - 2

            moves.coord[3].r = coord.r - 1
            moves.coord[3].c = coord.c + 2

            moves.coord[4].r = coord.r + 2
            moves.coord[4].c = coord.c - 1

            moves.coord[5].r = coord.r + 2
            moves.coord[5].c = coord.c + 1

            moves.coord[6].r = coord.r - 2
            moves.coord[6].c = coord.c - 1

            moves.coord[7].r = coord.r - 2
            moves.coord[7].c = coord.c + 1
            break;
        }
        case BQUEEN:
        case WQUEEN:
        {
            //todo
            break;
        }
        case BKING:
        case WKING:
        {
            //todo
            break;
        }
        case BBISHOP:
        case WBISHOP:
        {
            //todo
            break;
        }
        case BROOK:
        case WROOK:
        {
            moves.coord = (Coordinate*) malloc(14 * sizeof(Coordinate));
            int i = 0;
            for (int r = coord.r + 1; r < 8; ++r) {
                moves.coord[i].r = r;
                moves.coord[i].c = coord.c;
                ++i;
                if (b.squares[r][coord.c] != EMPTY) {
                    break;
                }
            }
            break;
        }
        case BPAWN:{
            //todo
            break;
        }
        case WPAWN:{
            //todo
            break;
        }
        case EMPTY:{
            //todo
            break;
        }
        default:
            moves.length = 0;
            moves.coord = Null;
    }

    return moves;
}
