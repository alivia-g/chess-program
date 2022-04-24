// to build: $ gcc -c game.c -o game.o
//           $ gcc ai.o analysis.o board.o pieces.o player.o ui.o util.o game.o -o game

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ai.h"
#include "analysis.h"
#include "board.h"
#include "pieces.h"
#include "ui.h"
#include "util.h"

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

struct Move ai_make_move(struct Board *b, enum player_color pcolor, char ai_type) {
    ai_type = tolower(ai_type);
    switch (ai_type) {
        case 'r': {
            return random_ai_make_move(b, pcolor);
        }
        case 'g': {
            return greedy_ai_make_move(b, pcolor);
        }
//        case 'm': {
//            return minimax_ai_make_move(b, pcolor);
//        }
//        case 'a': {
//            return alphabeta_ai_make_move(b, pcolor);
//        }
        default:
            printf("Invalid AI type: ai_make_move Error.");
    }
}

// turn-based game
void play_game(struct Board *b, enum player_color current_player, char white_player, char black_player) {
    struct Move new_move;
    do {
        if (current_player == white) {  // white's turn
            if (white_player == 'h') {
                new_move = human_make_move();
            } else {
                new_move = ai_make_move(b, current_player, white_player);
            }
        }
        if (current_player == black) {  // black's turn
            if (black_player == 'h') {
                new_move = human_make_move();
            } else {
                new_move = ai_make_move(b, current_player, black_player);
            }
        }
    } while (!is_move_valid(new_move.from, new_move.to, b, current_player));

    //printf("from %d,%d to %d,%d\n", new_move.from.r, new_move.from.c, new_move.to.r, new_move.to.c);

    make_move(b, new_move);
}

char get_player_type() {
    char player_type = 0;
    while (!valid_player_type(player_type)) {
        scanf("%c", &player_type);
        getchar();
        player_type = tolower(player_type);
    }
    return player_type;
}

void initialize_board(struct Board* b) {
    char board_type = 0;
    while (board_type != 'd' && board_type != 'c') {
        scanf("%c", &board_type);
        getchar();
        board_type = tolower(board_type);
    }
    if (board_type == 'd') {
        initialize_default_board(b);
    } else if (board_type == 'c') {
        initialize_custom_board(b);
    }
}

int main() {
    printf("Choose player type for white:\nHuman(h)\nRandom(r)\nGreedy(g)\nMinimax(m)\nAlpha-beta(a)\n");
    char white_player_type = get_player_type();
    printf("Choose player type for black:\nHuman(h)\nRandom(r)\nGreedy(g)\nMinimax(m)\nAlpha-beta(a)\n");
    char black_player_type = get_player_type();
    assert(valid_player_type(white_player_type));
    assert(valid_player_type(black_player_type));

    // initialize board
    struct Board b;
    clear(&b);
    printf("Choose board type: Default(d)/Custom(c)\n");
    initialize_board(&b);
    enum player_color current_player = white;
    while(!get_game_state(&b, current_player).game_over) {
        display_board(&b, current_player);
        printf("\n");
        play_game(&b, current_player, white_player_type, black_player_type);
        if (current_player == white) {
            current_player = black;
        } else if (current_player == black) {
            current_player = white;
        }
    }
    display_board(&b, current_player);

    // print game result
    int game_result = get_game_state(&b, white).special_value;
    if (game_result == 0) {
        printf("Game tied by stalemate.");
    } else if (game_result == -INF) {
        printf("Black won!");
    } else if (game_result == INF) {
        printf("White won!");
    } else {
        printf("get_game_state Error.");
    }

    return 0;
}
