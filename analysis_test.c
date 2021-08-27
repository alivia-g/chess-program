#include "assert.h"
#include "analysis.h"
#include "board.h"

void empty_board_test() {
    struct Board b;
    clear(&b);
    assert(get_player_value(&b, white) == 0);
    assert(get_player_value(&b, black) == 0);
    assert(get_game_value(&b, white) == 0);
    assert(get_game_value(&b, black) == 0);
}

void initial_board_test() {
    struct Board b;
    clear(&b);
    initialize_board(&b);
    assert(get_game_value(&b, white) == 0);
    assert(get_game_value(&b, black) == 0);
}

// Black has one pawn, white has two pawns
void extra_pawn_test() {
    struct Board b;
    clear(&b);
    place_piece_with_algebraic_position('P', "a2", &b);  // place 2 white pawns
    place_piece_with_algebraic_position('P', "b4", &b);
    place_piece_with_algebraic_position('p', "b2", &b);  // place black pawn
    assert(get_player_value(&b, white) == 2);
    assert(get_player_value(&b, black) == 1);
    assert(get_game_value(&b, white) == 1);
    assert(get_game_value(&b, black) == -1);
}

// Black has a king and bishop, white has only a king
void king_and_bishop_test() {
    struct Board b;
    clear(&b);
    place_piece_with_algebraic_position('K', "e1", &b);  // place white king
    place_piece_with_algebraic_position('k', "d7", &b);  // place black king
    place_piece_with_algebraic_position('b', "d3", &b);  // place black bishop
    assert(get_player_value(&b, white) == 1000);
    assert(get_player_value(&b, black) == 1003);
    assert(get_game_value(&b, white) == -3);
    assert(get_game_value(&b, black) == 3);
}

// Black has a knight and rook, white has a queen
void knight_and_rook_vs_queen_test() {
    struct Board b;
    clear(&b);
    place_piece_with_algebraic_position('Q', "c5", &b);  // place white queen
    place_piece_with_algebraic_position('n', "b6", &b);  // place black knight
    place_piece_with_algebraic_position('r', "d4", &b);  // place black rook
    assert(get_player_value(&b, white) == 9);
    assert(get_player_value(&b, black) == 8);
    assert(get_game_value(&b, white) == 1);
    assert(get_game_value(&b, black) == -1);
}

int main() {
    empty_board_test();
    printf("empty_board_test passed.\n");
    initial_board_test();
    printf("initial_board_test passed.\n");
    extra_pawn_test();
    printf("extra_pawn_test passed.\n");
    king_and_bishop_test();
    printf("king_and_bishop_test passed.\n");
    knight_and_rook_vs_queen_test();
    printf("knight_and_rook_vs_queen_test passed.\n");

    return 0;
}
