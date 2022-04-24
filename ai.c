#include <stdlib.h>
#include <time.h>

#include "ai.h"
#include "analysis.h"
#include "board.h"
#include "pieces.h"

// assumes the game is not over
struct Move random_ai_make_move(struct Board *b, enum player_color pcolor) {
    time_t t;
    srand((unsigned) time(&t));  // seed
    struct Move new_move;
    struct MoveList valid_moves;
    valid_moves.length = 0;
    do {
        new_move.from.r = rand() % 8;  // generate a random integer between 0 and 7
        new_move.from.c = rand() % 8;
        char piece_type = b->squares[new_move.from.r][new_move.from.c];
        if (get_color(piece_type) != pcolor) { continue; }
        valid_moves = get_valid_moves(new_move.from, b, pcolor);
    } while (valid_moves.length == 0);

    // randomly pick a move from valid moves
    new_move.to = valid_moves.coord[rand() % valid_moves.length];

    // TODO: choose a move based on AI difficulty
    return new_move;
}

struct Move greedy_ai_make_move(struct Board *b, enum player_color pcolor) {
    struct Move best_move;
    int highest_value_so_far = -INF;

    // for each square on the board
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            struct Move new_move;
            new_move.from.r = r;
            new_move.from.c = c;

            // if this piece is ours...
            char piece_type = b->squares[new_move.from.r][new_move.from.c];
            if (get_color(piece_type) != pcolor) { continue; }

            // get all its valid moves
            struct MoveList valid_moves = get_valid_moves(new_move.from, b, pcolor);

            for (int i = 0; i < valid_moves.length; ++i) {
                new_move.to = valid_moves.coord[i];

                // consider the board position after making this move
                struct Board new_board;
                copy_board(b, &new_board);
                make_move(&new_board, new_move);

                int new_board_value = get_game_value(&new_board, pcolor);
                // update the best move found so far
                if (new_board_value > highest_value_so_far) {
                    highest_value_so_far = new_board_value;
                    best_move = new_move;
                }
            }
        }
    }
    return best_move;
}
