#include <math.h>

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

void checkmate_test() {
    struct Board b;
    clear(&b);
    place_piece_with_algebraic_position('R', "a8", &b);  // place white rook
    place_piece_with_algebraic_position('k', "g8", &b);  // place black king
    place_piece_with_algebraic_position('p', "f7", &b);  // place three black pawns
    place_piece_with_algebraic_position('p', "g7", &b);
    place_piece_with_algebraic_position('p', "h7", &b);
    place_piece_with_algebraic_position('K', "e1", &b);  // place white king
    assert(is_king_in_check(&b, black) == true);
    assert(is_player_under_check_mated(&b, black) == true);
    assert(get_game_value(&b, black) == -2*INF);  // black is checkmated having a game value of -2*INFINITY
    assert(get_game_value(&b, white) == 2*INF);  // white checkmated black
    assert(get_player_value(&b, black) == -INF);
    assert(get_player_value(&b, white) == INF);
}

void stalemate_test() {
    struct Board b;
    clear(&b);
    place_piece_with_algebraic_position('k', "a8", &b);  // place black king
    place_piece_with_algebraic_position('K', "b6", &b);  // place white king
    place_piece_with_algebraic_position('N', "c6", &b);  // place white knight
    assert(is_king_in_check(&b, black) == false);
    assert(is_unchecked_player_stalemated(&b, black) == true);
    assert(get_game_value(&b, black) == 0);  // tie
    assert(get_game_value(&b, white) == 0);
    assert(get_player_value(&b, black) == 0);  // both players get zero for stalemate
    assert(get_player_value(&b, white) == 0);
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
    checkmate_test();
    printf("checkmate_test passed.\n");
    stalemate_test();
    printf("stalemate_test passed.\n");

    return 0;
}
