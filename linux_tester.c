// to build: $ make linux_tester

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ai.h"
#include "analysis.h"
#include "board.h"
#include "pieces.h"
#include "player.h"
#include "util.h"

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
            new_move = ai_make_move(b, current_player, white_player, white_difficulty);
        }
        if (current_player == black) {  // black's turn
            new_move = ai_make_move(b, current_player, black_player, black_difficulty);
        }
    } while (!is_move_valid(new_move.from, new_move.to, b, current_player));

    //printf("from %d,%d to %d,%d\n", new_move.from.r, new_move.from.c, new_move.to.r, new_move.to.c);
    fprintf(log_output, "%s\n", stringify_move(new_move));
    make_move(b, new_move);

    char player_type = current_player == white ? white_player : black_player;
    char ai_difficulty = current_player == white ? white_difficulty : black_difficulty;
    print_game_info(b, current_player, player_type, new_move, ai_difficulty);
}

// only for minimax and alpha-beta
int get_ai_difficulty(FILE* file_input) {
    int num_plies = 0;
    fscanf(file_input, "%d", &num_plies);

    return num_plies;
}

void initialize_board(struct Board* b, FILE* file_input) {
    for (int r = 7; r >= 0; --r) {
        char row[9];
        fgetc(file_input);  // get rid of '\n'
        fgets(row, 9, file_input);
        assert(strlen(row) == 8);
        for (int c = 0; c < 8; ++c) {
            b->squares[r][c] = row[c];
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong number of command line arguments.\n");
        printf("Usage: ./linux_tester test_data/[input_file.txt]\n");
        return -1;
    }
    FILE* input_test_data = fopen(argv[1], "r");

    FILE* log_output = fopen("moves_played.txt", "w");

    int difficulty = get_ai_difficulty(input_test_data);
    
    // number of plies to play
    int game_length = 0;
    fscanf(input_test_data, "%d", &game_length);
    
    // initialize board
    struct Board b;
    clear(&b);
    initialize_board(&b, input_test_data);
    enum player_color current_player = white;
    while (game_length-- > 0 && !get_game_state(&b, current_player).game_over) {
        printf("\n");
        play_game(&b, current_player, 'a', 'a', difficulty, difficulty, log_output);
        current_player = switch_turns(current_player);
    }
    
    // print game result
    int game_result = get_game_state(&b, white).special_value;
    if (game_result == 0) {
        printf("Game tied by stalemate.");
    } else if (game_result == -INF) {
        printf("Black won!");
    } else if (game_result == INF) {
        printf("White won!");
    }
    printf("\n");

    fclose(log_output);
    fclose(input_test_data);

    return 0;
}
