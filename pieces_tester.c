#include <stdio.h>

#include "board.h"
#include "pieces.h"
#include "ui.h"
#include "util.h"

const enum player_color CURRENT_PLAYER = white;

int number_of_pieces_alive(struct Board *b, enum player_color pcolor);


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
        //printf("piece type:    %c", piece_type);
        //printf("\nposition: %s", pos);

        // place piece on board
        place_piece_with_algebraic_position(piece_type, pos, &b);
        display_board(&b, CURRENT_PLAYER);
        // validate piece's possible moves, return list of valid moves
        struct Coordinate coord = algebraic_to_coordinate(pos);
        struct MoveList valid_moves = get_valid_moves(coord, &b, CURRENT_PLAYER);
        for (int i = 0; i < valid_moves.length; ++i) {
            //place_piece_with_algebraic_position(piece_type, valid_moves.coord[i], &b);
            printf("%d,%d\n", valid_moves.coord[i].r, valid_moves.coord[i].c);
        }

        if (number_of_pieces_alive(&b, black) > 0) {
            if (is_king_in_check(&b, black)) {
                if (is_player_under_check_mated(&b, black)) {
                    printf("Game over -- white won.\n");
                } else {
                    printf("The black King is under check! Be careful.\n");
                }
            } else if (is_unchecked_player_stalemated(&b, black)) {
                printf("Black is stalemated.\n");
            }
        }

        if (number_of_pieces_alive(&b, white) > 0) {
            if (is_king_in_check(&b, white)) {
                if (is_player_under_check_mated(&b, white)) {
                    printf("Game over -- black won.\n");
                } else {
                    printf("The white King is under check! Be careful.\n");
                }
            } else if (is_unchecked_player_stalemated(&b, white)) {
                printf("White is stalemated.\n");
            }
        }
    }
    return 0;
}

// helper function for checking the number of pieces alive on the board of a given player color
int number_of_pieces_alive(struct Board *b, enum player_color pcolor) {
    int num_of_pieces = 0;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (get_color(b->squares[r][c]) == pcolor) { num_of_pieces++; }
        }
    }
    return num_of_pieces;
}
