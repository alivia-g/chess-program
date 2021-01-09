#ifndef UI_H
#define UI_H

#include <windows.h>

#include "board.h"

/// source: stackoverflow.com/questions/44481821/is-it-possible-to-change-text-color-and-background-color-in-the-console-to-diffe/44482159#44482159
// foreground colors
const int WHITE_FOREGROUND = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const int BLACK_FOREGROUND = 0;
// background colors
const int GRAY_BACKGROUND = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
const int SILVER_BACKGROUND = BACKGROUND_INTENSITY;

void display_board(struct Board* b) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            int foreground = 0, background = 0;

            if ((r+c)%2 == 0) {
                background = GRAY_BACKGROUND;
            } else {
                background = SILVER_BACKGROUND;
            }

            if (isupper(b->squares[r][c])) {
                foreground = WHITE_FOREGROUND;
            } else if (islower(b->squares[r][c])) {
                foreground = BLACK_FOREGROUND;
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background | foreground);
            printf("%c", b->squares[r][c]);
        }
        printf("\n");
    }
    // reset colors
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_FOREGROUND | WHITE_FOREGROUND);
}

#endif // UI_H
