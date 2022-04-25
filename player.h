#ifndef PLAYER_H
#define PLAYER_H

// TODO: rename to color
enum player_color {black, white, none};

bool valid_player_type(char);

enum player_color switch_turns(enum player_color);

#endif  // PLAYER_H
