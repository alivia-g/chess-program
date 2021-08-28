#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "board.h"
#include "player.h"

// returns the total value of a player's pieces on the board
int get_player_value(struct Board *b, enum player_color pcolor);

// returns the difference between two players' values as the advantage of one player over the other
int get_game_value(struct Board *b, enum player_color pcolor);

static const int INF = 10000;  // some value that is larger than the sum of all pieces

#endif  // ANALYSIS_H
