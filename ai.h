#ifndef AI_H
#define AI_H

#include "analysis.h"
#include "board.h"

// pick a random piece and move
struct Move random_ai_make_move(struct Board *b, enum player_color pcolor);

// pick the best current one-ply move
struct Move greedy_ai_make_move(struct Board *b, enum player_color pcolor);

// pick the best move up to specified search depth
struct Move minimax_ai_make_move(struct Board *b, enum player_color pcolor, int max_depth);

struct Move alphabeta_ai_make_move(struct Board *b, enum player_color current_player, int max_depth);

#endif // AI_H
