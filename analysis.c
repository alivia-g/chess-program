#include <assert.h>

#include "analysis.h"
#include "board.h"
#include "player.h"

int get_player_value(struct Board *b, enum player_color pcolor) {
    int value = 0;

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (get_color(b->squares[r][c]) == pcolor) {
                value += get_piece_value(b->squares[r][c]);
            }
        }
    }

    return value;
}

int get_game_value(struct Board *b, enum player_color curr_player) {
    assert(curr_player != none);
    int value = 0;
    enum player_color opponent = (curr_player == white) ? black : white;
    return get_player_value(b, curr_player) - get_player_value(b, opponent);
}
