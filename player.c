#include <stdbool.h>

#include "player.h"

bool valid_player_type(char player_type) {
    return player_type == 'h' ||
    player_type == 'r' ||
    player_type == 'g' ||
    player_type == 'm' ||
    player_type == 'a';
}

enum player_color switch_turns(enum player_color pcolor) {
    if (pcolor == black) {
        return white;
    } else if (pcolor == white) {
        return black;
    } else {
        return none;
    }
}
