#ifndef AI_H
#define AI_H

#include "analysis.h"
#include "board.h"

struct Move random_ai_make_move(struct Board *b, enum player_color pcolor);

#endif // AI_H
