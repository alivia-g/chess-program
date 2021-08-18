#include <stdio.h>

#include "board.h"
#include "pieces.h"
#include "ui.h"
#include "util.h"

const enum player_color CURRENT_PLAYER = white;

int main() {
    // create board
    struct Board b;
    clear(&b);
    //initialize_board(&b);
    display_board(&b, CURRENT_PLAYER);
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
        char old_piece = place_piece_with_algebraic_position(piece_type, pos, &b);
        //
        display_board(&b, CURRENT_PLAYER);
        // validate piece's possible moves, return list of valid moves
        struct Coordinate coord = algebraic_to_coordinate(pos);
        struct MoveList valid_moves = get_valid_moves(coord, &b);
        printf("Number of valid moves: %d\n", valid_moves.length);
        printf("Valid moves are:\n");
        for (int i = 0; i < valid_moves.length; ++i) {
            //place_piece_with_algebraic_position(piece_type, valid_moves.coord[i], &b);
            printf("%d,%d\n", valid_moves.coord[i].r, valid_moves.coord[i].c);
        }
        if (is_king_in_check(&b, black)) { printf("The black King is under check! Be careful.\n"); }
        if (is_king_in_check(&b, white)) { printf("The white King is under check! Be careful.\n"); }
    }
    return 0;
}
