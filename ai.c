#include <stdlib.h>
#include <time.h>

#include "ai.h"
#include "analysis.h"
#include "board.h"
#include "pieces.h"
#include "player.h"
#include "util.h"

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
struct Move random_ai_make_move(struct Board *b, enum player_color current_player) {
    time_t t;
    srand((unsigned) time(&t));  // seed
    struct Move new_move;
    struct MoveList valid_moves;
    valid_moves.length = 0;
    do {
        new_move.from.r = rand() % 8;  // generate a random integer between 0 and 7
        new_move.from.c = rand() % 8;
        char piece_type = b->squares[new_move.from.r][new_move.from.c];
        if (get_color(piece_type) != current_player) { continue; }
        valid_moves = get_valid_moves(new_move.from, b, current_player);
    } while (valid_moves.length == 0);

    // randomly pick a move from valid moves
    new_move.to = valid_moves.coord[rand() % valid_moves.length];

    clear_movelist(&valid_moves);  // free memory

    return new_move;
}

struct Move greedy_ai_make_move(struct Board *b, enum player_color current_player) {
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
        if (get_color(piece_type) != current_player) { continue; }

        // get all its valid moves
        struct MoveList valid_moves = get_shuffled_valid_moves(new_move.from, b, current_player);

        for (int i = 0; i < valid_moves.length; ++i) {
            new_move.to = valid_moves.coord[i];

            // consider the board position after making this move
            struct Board new_board;
            copy_board(b, &new_board);

            make_move(&new_board, new_move);

            int new_board_value = get_game_value(&new_board, current_player);
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
int minimax_recursion(struct Board *b, enum player_color current_player, int depth, struct Move* best_move, int* states_counter) {
    (*states_counter)++;

    // base case
    if (depth == 0 || get_game_state(b, current_player).game_over) {
        return get_game_value(b, current_player);
    }

    // general case
    int minimax = INF;
    struct MoveList shuffled_squares = get_shuffled_coords();

    bool found_any_move = false;
    // for each square on the board
    for (int i = 0; i < shuffled_squares.length; ++i) {
        struct Move new_move;
        new_move.from.r = shuffled_squares.coord[i].r;
        new_move.from.c = shuffled_squares.coord[i].c;

        // if this piece is ours...
        char piece_type = b->squares[new_move.from.r][new_move.from.c];
        if (get_color(piece_type) != current_player) { continue; }

        // get all its valid moves
        struct MoveList valid_moves = get_shuffled_valid_moves(new_move.from, b, current_player);

        for (int i = 0; i < valid_moves.length; ++i) {
            new_move.to = valid_moves.coord[i];
            // consider the board position after making this move
            char old_from = b->squares[new_move.from.r][new_move.from.c];
            char old_to = b->squares[new_move.to.r][new_move.to.c];

            make_move(b, new_move);

            struct Move opponent_move;  // dummy - not used

            int new_board_value = minimax_recursion(b, switch_turns(current_player), depth-1, &opponent_move, states_counter);
            // update the best move found so far
            if (new_board_value < minimax || !found_any_move) {
                minimax = new_board_value;
                *best_move = new_move;
                found_any_move = true;
            }
            b->squares[new_move.from.r][new_move.from.c] = old_from;
            b->squares[new_move.to.r][new_move.to.c] = old_to;
        }
        clear_movelist(&valid_moves);
    }
    clear_movelist(&shuffled_squares);
    return -minimax;
}

struct Move minimax_ai_make_move(struct Board *b, enum player_color current_player, int max_depth) {
    struct Move best_move;
    int num_states_evaluated = 0;

    minimax_recursion(b, current_player, max_depth, &best_move, &num_states_evaluated);

    static FILE *log_output_white_player = 0;
    open_log_file(&log_output_white_player, "minimax_output_white_player.txt");
    static FILE *log_output_black_player = 0;
    open_log_file(&log_output_black_player, "minimax_output_black_player.txt");

    FILE* log_output_current_player = (current_player == white ? log_output_white_player : log_output_black_player);

    // log the number of states evaluated at this move
    fprintf(log_output_current_player, "%d\n", num_states_evaluated);

    return best_move;
}

// alpha: lower bound on white player's value
// beta: lower bound on black player's value
int alphabeta_recursion(struct Board *b, enum player_color current_player, int depth, int alpha, int beta, struct Move* best_move, int* states_counter) {
    // printf("alpha_beta_recursion(b, %d, %d, %d, %d, best_move, %d\n", current_player, depth, alpha, beta, *states_counter);
    (*states_counter)++;

    // base case
    if (depth == 0 || get_game_state(b, current_player).game_over) {
        return get_game_value(b, current_player);
    }

    struct MoveList shuffled_squares = get_shuffled_coords();

    bool found_any_move = false;

    // for each square on the board
    for (int i = 0; i < shuffled_squares.length; ++i) {
        struct Move new_move;
        new_move.from.r = shuffled_squares.coord[i].r;
        new_move.from.c = shuffled_squares.coord[i].c;

        // if this piece is ours...
        char piece_type = b->squares[new_move.from.r][new_move.from.c];
        if (get_color(piece_type) != current_player) { continue; }

        // get all its valid moves
        struct MoveList valid_moves = get_shuffled_valid_moves(new_move.from, b, current_player);

        for (int i = 0; i < valid_moves.length; ++i) {
            new_move.to = valid_moves.coord[i];
            // consider the board position after making this move
            char old_from = b->squares[new_move.from.r][new_move.from.c];
            char old_to = b->squares[new_move.to.r][new_move.to.c];

            make_move(b, new_move);

            struct Move opponent_response;  // dummy - not used

            int opponent_value = alphabeta_recursion(b, switch_turns(current_player), depth - 1, alpha, beta, &opponent_response, states_counter);
            int our_value = -opponent_value;

            int fail_hard_cutoff = 0;
            bool prune = false;
            if (current_player == white) {
                 if (opponent_value <= beta && !found_any_move) {
                     // fail-hard beta cutoff
                     fail_hard_cutoff = -beta;
                     prune = true;
                 } else if (our_value > alpha || !found_any_move) {
                     // update alpha if white can improve its lower bound
                     alpha = our_value;
                     *best_move = new_move;
                     found_any_move = true;
                 }
            } else if (current_player == black) {
                 if (opponent_value <= alpha && !found_any_move) {
                     // fail-hard alpha cutoff
                     fail_hard_cutoff = -alpha;
                     prune = true;
                 } else if (our_value > beta || !found_any_move) {
                     // update beta if black can improve its upper bound
                     beta = our_value;
                     *best_move = new_move;
                     found_any_move = true;
                 }
            }

            // move piece back after evaluating this position
            b->squares[new_move.from.r][new_move.from.c] = old_from;
            b->squares[new_move.to.r][new_move.to.c] = old_to;
            if (prune) {
                clear_movelist(&valid_moves);
                clear_movelist(&shuffled_squares);
                return fail_hard_cutoff;
            }
        }
        clear_movelist(&valid_moves);
    }
    clear_movelist(&shuffled_squares);
    return current_player == white ? alpha : beta;
}

struct Move alphabeta_ai_make_move(struct Board *b, enum player_color current_player, int max_depth) {
    struct Move best_move;
    int num_states_evaluated = 0;

    alphabeta_recursion(b, current_player, max_depth, -INF, -INF, &best_move, &num_states_evaluated);

    static FILE *log_output_white_player = 0;
    open_log_file(&log_output_white_player, "alphabeta_output_white_player.txt");
    static FILE *log_output_black_player = 0;
    open_log_file(&log_output_black_player, "alphabeta_output_black_player.txt");

    FILE* log_output_current_player = (current_player == white ? log_output_white_player : log_output_black_player);

    // log the number of states evaluated at this move
    fprintf(log_output_current_player, "%d\n", num_states_evaluated);

    return best_move;
}
