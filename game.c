#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#include "analysis.h"
#include "board.h"
#include "pieces.h"
#include "ui.h"
#include "util.h"

struct Move {
    struct Coordinate from;
    struct Coordinate to;
};

struct Move human_make_move() {
    struct Move new_move;

    char from[3];
    printf("Enter the location of the piece that you want to move: ");
    scanf("%s", from);
    new_move.from = algebraic_to_coordinate(from);

    char to[3];
    printf("Enter where you want to place the selected piece: ");
    scanf("%s", to);
    new_move.to = algebraic_to_coordinate(to);

    return new_move;
}

struct Move ai_make_move() {
    struct Move new_move;
    new_move.from.r = 0;
    new_move.from.c = 0;
    new_move.to.r = 1;
    new_move.to.c = 1;
    // TODO: choose a move based on AI difficulty
    return new_move;
}

// Assumes that the input move is valid
void make_move(struct Board *b, struct Move move) {
    // Remove piece from move.from
    char old_piece = place_piece_on_coordinate(EMPTY, move.from, b);
    // Place a piece at move.to
    place_piece_on_coordinate(old_piece, move.to, b);
}

// turn-based game
void play_game(struct Board *b, enum player_color current_player, char white_player, char black_player) {
    struct Move new_move;
    do {
        if (current_player == white) {  // white's turn
            if (white_player == 'h') {
                new_move = human_make_move();
            } else if (white_player == 'c') {
                new_move = ai_make_move();
            }
        }
        if (current_player == black) {  // black's turn
            if (black_player == 'h') {
                new_move = human_make_move();
            } else if (black_player == 'c') {
                new_move = ai_make_move();
            }
        }
    } while (!is_move_valid(new_move.from, new_move.to, b, current_player));

    make_move(b, new_move);
}

char get_player_type() {
    char player_type = 0;
    while (player_type != 'h' && player_type != 'c') {
        scanf("%c", &player_type);
        getchar();
        player_type = tolower(player_type);
    }
    return player_type;
}

int main() {
    printf("Choose player type for white: Human(h)/Computer(c)\n");
    char white_player_type = get_player_type();
    printf("Choose player type for black: Human(h)/Computer(c)\n");
    char black_player_type = get_player_type();
    assert(white_player_type == 'h' || white_player_type == 'c');
    assert(black_player_type == 'h' || black_player_type == 'c');

    // initialize board
    struct Board b;
    clear(&b);
    initialize_board(&b);
    enum player_color current_player = white;
    while(!get_game_state(&b, current_player).game_over) {
        display_board(&b, current_player);
        play_game(&b, current_player, white_player_type, black_player_type);
        if (current_player == white) {
            current_player = black;
        } else if (current_player == black) {
            current_player = white;
        }
    }
    // print game result
    return 0;
}
