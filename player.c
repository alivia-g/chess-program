#include <stdbool.h>

#include "player.h"

bool valid_player_type(char player_type) {
    return player_type == 'h' ||
    player_type == 'r' ||
    player_type == 'm' ||
    player_type == 'a';
}
