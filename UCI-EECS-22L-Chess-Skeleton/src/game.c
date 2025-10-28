// game.c stub
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "board.h"
#include "io.h"
#include "move_validator.h"
#include "check.h"
#include "ui/ui.h"
#include "player.h"

void game_loop() {
  // Initialize the game
  board_init();

  while(true) {
    // Displays the board
    ui_draw_board();

    char current_player = player_get_current();
    //printf("Debug: Current player is %c\n", current_player);

    // Checks if the current player is in checkmate
    if(is_checkmate(current_player)){
      ui_draw_board();
      char winner = (current_player == 'W') ? 'B' : 'W'; // The *other* player wins
      char message[100];
      sprintf(message, "Checkmate! Player %c wins!", winner);
      ui_show_message(message);
      break;
    }

    // Checks if the current player is in check
    if(is_in_check(current_player)){
      ui_draw_board();
      char message[100];
      sprintf(message, "Check! Player %c is in check!", current_player);
      ui_show_message(message);
    }

    // Get move from user
    Move move;
    printf("Player %c, enter your move (e.g., e2 e4): ", current_player);
    if (!io_get_move(&move)) {
      ui_show_message("Invalid move. Try again.");
      continue;
    }

    if (!is_valid_move(move, current_player)) {
      ui_show_message("Invalid move. Try again.");
      continue;
    }

    // Apply the move
    char piece = board_get(move.from_row, move.from_col);
    board_set(move.from_row, move.from_col, '.'); // Clear the source square
    board_set(move.to_row, move.to_col, piece); // Set the target square
    player_switch(); // Switch players
   
  }
}