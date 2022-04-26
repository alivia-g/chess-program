// to build: $ gcc -c windows_game.c -o windows_game.o
//           $ gcc ai.o analysis.o board.o pieces.o player.o util.o windows_ui.o windows_game.o -o windows_game

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ai.h"
#include "analysis.h"
#include "board.h"
#include "pieces.h"
#include "player.h"
#include "util.h"
#include "windows_ui.h"

struct Move human_make_move() {
    struct Move new_move;

    char from[3];
    printf("Enter the location of the piece that you want to move: ");
    scanf("%s", from);
    new_move.from = algebraic_to_coordinate(from);

    char to[3];
    printf("Enter where you want to place the selected piece: ");
    scanf("%s", to);
    new_move.to = algebraic_to_coordinate(to);

    return new_move;
}

struct Move ai_make_move(struct Board *b, enum player_color pcolor, char ai_type, int difficulty) {
    ai_type = tolower(ai_type);
    switch (ai_type) {
        case 'r': {
            return random_ai_make_move(b, pcolor);
        }
        case 'g': {
            return greedy_ai_make_move(b, pcolor);
        }
        case 'm': {
            return minimax_ai_make_move(b, pcolor, difficulty);
        }
        case 'a': {
            return alphabeta_ai_make_move(b, pcolor, difficulty);
        }
        default:
            printf("Invalid AI type: ai_make_move Error.");
    }
    exit(-1);
}

void print_game_info(struct Board *b, enum player_color current_player, char player_type, struct Move last_move, int ai_difficulty) {
    // print the current player and the last move they played as well as the game value
    switch (player_type) {
        case 'h': {
            printf("Human");
            break;
        }
        case 'r': {
            printf("Random AI (0 ply)");
            break;
        }
        case 'g': {
            printf("Greedy AI (1 ply)");
            break;
        }
        case 'm': {
            printf("Minimax AI (%d ply)", ai_difficulty);
            break;
        }
        case 'a': {
            printf("Alpha-beta AI (%d ply)", ai_difficulty);
            break;
        }
        default:
            printf("Unknown player");
    }

    char* move_string = stringify_move(last_move);
    printf(" plays %s as ", move_string);
    free(move_string);

    if (current_player == black) {
        printf("black");
    } else if (current_player == white) {
        printf("white");
    }
    printf("\n");
    printf("Current value: %d\n", get_game_value(b, current_player));
}

// turn-based game
void play_game(struct Board *b, enum player_color current_player, char white_player, char black_player, int white_difficulty, int black_difficulty, FILE* log_output) {
    struct Move new_move;
    do {
        if (current_player == white) {  // white's turn
            if (white_player == 'h') {
                new_move = human_make_move();
            } else {
                new_move = ai_make_move(b, current_player, white_player, white_difficulty);
            }
        }
        if (current_player == black) {  // black's turn
            if (black_player == 'h') {
                new_move = human_make_move();
            } else {
                new_move = ai_make_move(b, current_player, black_player, black_difficulty);
            }
        }
    } while (!is_move_valid(new_move.from, new_move.to, b, current_player));

    //printf("from %d,%d to %d,%d\n", new_move.from.r, new_move.from.c, new_move.to.r, new_move.to.c);
    fprintf(log_output, "%s\n", stringify_move(new_move));
    make_move(b, new_move);

    char player_type = current_player == white ? white_player : black_player;
    char ai_difficulty = current_player == white ? white_difficulty : black_difficulty;
    print_game_info(b, current_player, player_type, new_move, ai_difficulty);
}

int get_ai_difficulty(char player_type) {
    // check for special cases
    if (player_type == 'h') return -1;
    if (player_type == 'r') return 0;
    if (player_type == 'g') return 1;

    int num_plies = 0;
    while (num_plies <= 0) {
        printf("Enter AI difficulty (i.e. number of plies): ");
        scanf("%d", &num_plies);
        getchar();
    }
    return num_plies;
}

char get_player_type() {
    char player_type = 0;
    while (!valid_player_type(player_type)) {
        scanf("%c", &player_type);
        getchar();
        player_type = tolower(player_type);
    }
    return player_type;
}

void initialize_board(struct Board* b) {
    char board_type = 0;
    while (board_type != 'd' && board_type != 'c') {
        scanf("%c", &board_type);
        getchar();
        board_type = tolower(board_type);
    }
    if (board_type == 'd') {
        initialize_default_board(b);
    } else if (board_type == 'c') {
        initialize_custom_board(b);
    }
}

int main() {
    FILE* log_output = fopen("moves_played.txt", "w");

    printf("Choose player type for white:\nHuman(h)\nRandom(r)\nGreedy(g)\nMinimax(m)\nAlpha-beta(a)\n");
    char white_player_type = get_player_type();
    int white_difficulty = get_ai_difficulty(white_player_type);
    assert(valid_player_type(white_player_type));

    printf("Choose player type for black:\nHuman(h)\nRandom(r)\nGreedy(g)\nMinimax(m)\nAlpha-beta(a)\n");
    char black_player_type = get_player_type();
    int black_difficulty = get_ai_difficulty(black_player_type);
    assert(valid_player_type(black_player_type));

    // initialize board
    struct Board b;
    clear(&b);
    printf("Choose board type: Default(d)/Custom(c)\n");
    initialize_board(&b);
    enum player_color current_player = white;
    while(!get_game_state(&b, current_player).game_over) {
        display_board(&b, current_player);
        printf("\n");
        play_game(&b, current_player, white_player_type, black_player_type, white_difficulty, black_difficulty, log_output);
        current_player = switch_turns(current_player);
    }
    display_board(&b, current_player);

    // print game result
    int game_result = get_game_state(&b, white).special_value;
    if (game_result == 0) {
        printf("Game tied by stalemate.");
    } else if (game_result == -INF) {
        printf("Black won!");
    } else if (game_result == INF) {
        printf("White won!");
    } else {
        printf("get_game_state Error.");
    }
    printf("\n");

    fclose(log_output);

    return 0;
}
