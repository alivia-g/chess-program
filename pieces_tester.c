#include <stdio.h>

#include "board.h"
#include "pieces.h"
#include "ui.h"
#include "util.h"

int main() {
    // create board
    struct Board b;
    clear(&b);
    // initialize_board(&b);
    display_board(&b);
    // enter a piece
    char piece_type;
    char pos[3];
    scanf("%c", &piece_type);
    scanf("%s", pos);
    //printf("piece type: %c", piece_type);
    //printf("\nposition: %s", pos);

    // place piece on board
    place_piece(piece_type, pos, &b);
    display_board(&b);
    // validate piece's possible moves, return list of valid moves
    struct Coordinate coord = algebraic_to_coordinate(pos);
    struct MoveList valid_moves = get_valid_moves(coord, piece_type, &b);
    printf("Length: %d", valid_moves.length);
    return 0;
}
