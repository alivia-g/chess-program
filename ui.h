#ifndef UI_H
#define UI_H

#include <windows.h>

#include "board.h"
#include "player.h"

/// stolen from Cody Gray https://stackoverflow.com/users/366904/cody-gray
/// From StackOverflow
/// From https://stackoverflow.com/questions/44481821/is-it-possible-to-change-text-color-and-background-color-in-the-console-to-diffe/44482159#44482159
// foreground colors
static const int WHITE_FOREGROUND = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
static const int BLACK_FOREGROUND = 0;
// background colors
static const int GRAY_BACKGROUND = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
static const int SILVER_BACKGROUND = BACKGROUND_INTENSITY;

void display_board(struct Board* b, enum player_color player);

#endif // UI_H
