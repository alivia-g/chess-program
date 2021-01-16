#include "ui.h"

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
