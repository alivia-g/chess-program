#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

const char EMPTY = ' ';

// white pieces
const char WKNIGHT = 'N';
const char WQUEEN = 'Q';
const char WKING = 'K';
const char WBISHOP = 'B';
const char WROOK = 'R';
const char WPAWN = 'P';
// black pieces
const char BKNIGHT = 'n';
const char BQUEEN = 'q';
const char BKING = 'k';
const char BBISHOP = 'b';
const char BROOK = 'r';
const char BPAWN = 'p';

/// source: stackoverflow.com/questions/44481821/is-it-possible-to-change-text-color-and-background-color-in-the-console-to-diffe/44482159#44482159
// foreground colors
const int WHITE_FOREGROUND = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const int BLACK_FOREGROUND = 0;
// background colors
const int GRAY_BACKGROUND = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
const int SILVER_BACKGROUND = BACKGROUND_INTENSITY;

struct Board {
    char squares[8][8];
};

void clear(struct Board *b) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            b->squares[r][c] = EMPTY;
        }
    }
}

struct Coordinate {
    int r, c;
};

struct Coordinate algebraic_to_coordinate(char *pos) {
    assert(strlen(pos) == 2);
    struct Coordinate coord;
    coord.r = pos[1] - '1';
    coord.c = pos[0] - 'a';
    return coord;
}

char place_piece(char piece, char *pos, struct Board *b) {
    struct Coordinate coord = algebraic_to_coordinate(pos);
    char old_piece = b->squares[coord.r][coord.c];
    // place piece on board
    b->squares[coord.r][coord.c] = piece;
    return old_piece;
}

void initialize_board(struct Board* b) {
    place_piece(BROOK, "a8", b);
    place_piece(BKNIGHT, "b8", b);
    place_piece(BBISHOP, "c8", b);
    place_piece(BQUEEN, "d8", b);
    place_piece(BKING, "e8", b);
    place_piece(BBISHOP, "f8", b);
    place_piece(BKNIGHT, "g8", b);
    place_piece(BROOK, "h8", b);

    place_piece(WROOK, "a1", b);
    place_piece(WKNIGHT, "b1", b);
    place_piece(WBISHOP, "c1", b);
    place_piece(WQUEEN, "d1", b);
    place_piece(WKING, "e1", b);
    place_piece(WBISHOP, "f1", b);
    place_piece(WKNIGHT, "g1", b);
    place_piece(WROOK, "h1", b);

    // place black pawns
    for (char f = 'a'; f <= 'h'; ++f) {
        char s[3] = "a2";
        s[0] = f;
        place_piece(WPAWN, s, b);
    }
    // place white pawns
    for (char f = 'a'; f <= 'h'; ++f) {
        char s[3] = "a7";
        s[0] = f;
        place_piece(BPAWN, s, b);
    }
}

// validate coordinate
bool validate_coord(struct Coordinate coord) {
    return (coord.r >= 0)&&(coord.r <= 7)&&(coord.c >= 0)&&(coord.c <= 7);
}

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

// create a function to copy values from one board to another
void copy_board(struct Board* b1, struct Board* b2) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            b2->squares[r][c] = b1->squares[r][c];
        }
    }
}

int main(){
    struct Board b;
    clear(&b);
    initialize_board(&b);
    display_board(&b);

    struct Board b2;
    clear(&b2);
    printf("\n");
    display_board(&b2);
    printf("\n");
    copy_board(&b, &b2);
    display_board(&b2);

    return 0;
}
