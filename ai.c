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
