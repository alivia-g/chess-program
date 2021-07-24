#include <stdio.h>

#include "pieces.h"
#include "ui.h"

int main() {
    // create board
    struct Board b;
    clear(&b);
    initialize_board(&b);
    display_board(&b);
    // enter a piece
    char piece_type;
    scanf("%c", &piece_type);
    printf("%c", piece_type);
    // place piece on board
    // validate piece's possible moves, return list of valid moves
    return 0;
}
