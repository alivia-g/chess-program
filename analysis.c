#include <assert.h>
#include <stdbool.h>

#include "analysis.h"
#include "board.h"
#include "pieces.h"
#include "player.h"

// TODO: Add other cases (e.g. king + bishop or king + knight)
bool drawn_endgame(struct Board *b) {
    // count number of pieces
    int num_pieces = 0;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            num_pieces += get_piece_value(b->squares[r][c]) > 0;
        }
    }
    return num_pieces == 2;  // only two kings left
}

// returns information on if the game is over and the game state value
struct GameState get_game_state(struct Board *b, enum player_color curr_player) {
    struct GameState state;
    // initialize state
    state.game_over = false;
    state.special_value = -1;

    enum player_color opponent = (curr_player == white) ? black : white;
    bool curr_king_in_check = is_king_in_check(b, curr_player);
    bool opponent_king_in_check = is_king_in_check(b, opponent);

    if (curr_king_in_check && is_player_under_check_mated(b, curr_player)) {  // being checkmated by opponent
        state.game_over = true;
        state.special_value = -INF;
    } else if (!curr_king_in_check && is_unchecked_player_stalemated(b, curr_player)) {  // being stalemated
        state.game_over = true;
        state.special_value = 0;
    } else if (opponent_king_in_check && is_player_under_check_mated(b, opponent)) {  // checkmated opponent
        state.game_over = true;
        state.special_value = INF;
    } else if (!opponent_king_in_check && is_unchecked_player_stalemated(b, opponent)) {  // stalemated opponent
        state.game_over = true;
        state.special_value = 0;
    } else if (drawn_endgame(b)) {  // game results in a tie (neither player can deliver checkmate anymore)
        state.game_over = true;
        state.special_value = 0;
    }
    return state;
}

// returns player's material value at current game state
int get_pieces_value(struct Board *b, enum player_color curr_player) {
    int value = 0;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (get_color(b->squares[r][c]) == curr_player) {
                value += get_piece_value(b->squares[r][c]);
            }
        }
    }
    return value;
}

// returns player's material value (or +/- INF in case of checkmate) at current game state
int get_player_value(struct Board *b, enum player_color curr_player) {
    struct GameState state = get_game_state(b, curr_player);
    if (state.game_over) { return state.special_value; }

    return get_pieces_value(b, curr_player);
}

// returns the game state value of the current player
int get_game_value(struct Board *b, enum player_color curr_player) {
    assert(curr_player != none);
    enum player_color opponent = (curr_player == white) ? black : white;
    return get_player_value(b, curr_player) - get_player_value(b, opponent);
}
