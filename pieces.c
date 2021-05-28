#include "pieces.h"

struct MoveList {
    int length;
    Coordinate[] coord;
};

struct MoveList get_valid_moves(struct Coordinate coord, char piece_type) {
    struct MoveList moves;
    
    switch (piece_type) {
        case BKNIGHT:
        case WKNIGHT:
        {
            moves.coord = (Coordinate*) malloc(8 * sizeof(Coordinate));
            moves.coord[0].r = coord.r -
            moves.coord[0].c =
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
            //todo
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
