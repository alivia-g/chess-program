#include <stdio.h>

#include "board.h"
#include "ui.h"

int main() {
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
