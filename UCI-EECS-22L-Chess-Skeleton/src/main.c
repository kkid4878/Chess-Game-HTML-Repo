#include "game.h"
#include "ui/ui.h"
#include "board.h"
#include <stdio.h>

int main() {
    ui_init();

    /*printf("Debug: Testing board_get and board_set...\n");
    char piece = board_get(0, 0); // Should return 'R'
    printf("Debug: Piece at (0, 0) is '%c'\n", piece);

    board_set(4, 4, 'P'); // Place a white pawn at (4, 4)
    board_print(); // Print the board to verify the update*/

    game_loop();
    ui_cleanup();
    return 0;
}
