#include <stdlib.h>
#include <time.h>
#include <stdio.h>  ///

#include "ai.h"
#include "analysis.h"
#include "board.h"
#include "pieces.h"
#include "player.h"

// randomly orders all squares on the board
struct MoveList get_shuffled_coords() {
    struct MoveList permutation;

    initialize_movelist(&permutation, 64);

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            int i = r * 8 + c;
            permutation.coord[i].r = r;
            permutation.coord[i].c = c;
        }
    }

    shuffle_movelist(&permutation);

//    for (int i = 0; i < permutation.length; ++i) {
//        printf("%s\n", coordinate_to_algebraic(permutation.coord[i]));
//    }

    return permutation;
}

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

    clear_movelist(&valid_moves);  // free memory

    return new_move;
}

struct Move greedy_ai_make_move(struct Board *b, enum player_color pcolor) {
    struct Move best_move;
    int highest_value_so_far = -INF;

    struct MoveList shuffled_squares = get_shuffled_coords();

    // for each square on the board
    for (int i = 0; i < shuffled_squares.length; ++i) {
        struct Move new_move;
        new_move.from.r = shuffled_squares.coord[i].r;
        new_move.from.c = shuffled_squares.coord[i].c;

        // if this piece is ours...
        char piece_type = b->squares[new_move.from.r][new_move.from.c];
        if (get_color(piece_type) != pcolor) { continue; }

        // get all its valid moves
        struct MoveList valid_moves = get_shuffled_valid_moves(new_move.from, b, pcolor);

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
        clear_movelist(&valid_moves);
    }
    clear_movelist(&shuffled_squares);

    return best_move;
}

// returns the maximum value that the current player can get
int minimax_recursion(struct Board *b, enum player_color pcolor, int depth, struct Move* best_move, FILE* output) {
    // base case
    if (depth == 0 || get_game_state(b, pcolor).game_over) {
        return get_game_value(b, pcolor);
    }

    // general case
    int minimax = INF;
    struct MoveList shuffled_squares = get_shuffled_coords();

    // for each square on the board
    for (int i = 0; i < shuffled_squares.length; ++i) {
        struct Move new_move;
        new_move.from.r = shuffled_squares.coord[i].r;
        new_move.from.c = shuffled_squares.coord[i].c;

        // if this piece is ours...
        char piece_type = b->squares[new_move.from.r][new_move.from.c];
        if (get_color(piece_type) != pcolor) { continue; }

        // get all its valid moves
        struct MoveList valid_moves = get_shuffled_valid_moves(new_move.from, b, pcolor);

        for (int i = 0; i < valid_moves.length; ++i) {
            new_move.to = valid_moves.coord[i];
            // consider the board position after making this move
            struct Board new_board;
            copy_board(b, &new_board);
            make_move(&new_board, new_move);
            struct Move opponent_move;  // dummy - not used
            int new_board_value = minimax_recursion(&new_board, switch_turns(pcolor), depth-1, &opponent_move, output);
            // update the best move found so far
            if (new_board_value < minimax) {
                minimax = new_board_value;
                *best_move = new_move;
            }
        }
        clear_movelist(&valid_moves);
    }
    clear_movelist(&shuffled_squares);
    return -minimax;
}

struct Move minimax_ai_make_move(struct Board *b, enum player_color pcolor, int max_depth) {
    FILE *log_output = fopen("log_output.txt", "w");

    struct Move best_move;
    minimax_recursion(b, pcolor, max_depth, &best_move, log_output);

    fclose(log_output);

    return best_move;
}
