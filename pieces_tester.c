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
    while(1) {
        // enter a piece
        char piece_type;
        char pos[3];
        printf("Enter piece type (or space to quit): ");
        scanf("%c", &piece_type);
        getchar();
        if (piece_type == EMPTY) {
            break;
        }
        printf("Enter position to place piece: ");
        scanf("%s", pos);
        getchar();
        //printf("piece type: %c", piece_type);
        //printf("\nposition: %s", pos);

        // place piece on board
        place_piece(piece_type, pos, &b);
        display_board(&b);
        // validate piece's possible moves, return list of valid moves
        struct Coordinate coord = algebraic_to_coordinate(pos);
        struct MoveList valid_moves = get_valid_moves(coord, piece_type, &b);
        printf("Number of valid moves: %d\n", valid_moves.length);
        printf("Valid moves are:\n");
        for (int i = 0; i < valid_moves.length; ++i) {
            //place_piece(piece_type, valid_moves.coord[i], &b);
            printf("%d,%d\n", valid_moves.coord[i].r, valid_moves.coord[i].c);
        }
    }
    return 0;
}
