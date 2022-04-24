#ifndef AI_H
#define AI_H

#include "analysis.h"
#include "board.h"

// pick a random piece and move
struct Move random_ai_make_move(struct Board *b, enum player_color pcolor);

// pick the best current one-ply move
struct Move greedy_ai_make_move(struct Board *b, enum player_color pcolor);

#endif // AI_H
