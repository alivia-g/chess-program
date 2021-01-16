#ifndef UI_H
#define UI_H

#include <windows.h>

#include "board.h"

/// stolen from Cody Gray https://stackoverflow.com/users/366904/cody-gray
/// From StackOverflow
/// From https://stackoverflow.com/questions/44481821/is-it-possible-to-change-text-color-and-background-color-in-the-console-to-diffe/44482159#44482159
// foreground colors
const int WHITE_FOREGROUND = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const int BLACK_FOREGROUND = 0;
// background colors
const int GRAY_BACKGROUND = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
const int SILVER_BACKGROUND = BACKGROUND_INTENSITY;

#endif // UI_H
