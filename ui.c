#include <ctype.h>
#include <stdio.h>

#include "ui.h"
#include "player.h"

void display_board(struct Board* b, enum player_color player) {
    int start, end, increment;
    if (player == black) {
        start = 0;
        end = 8;
        increment = 1;
    } else if (player == white) {
        start = 7;
        end = -1;
        increment = -1;
    }
    for (int r = start; r != end; r = r + increment) {
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
        // reset colors
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK_FOREGROUND | WHITE_FOREGROUND);
        printf("\n");
    }
}
