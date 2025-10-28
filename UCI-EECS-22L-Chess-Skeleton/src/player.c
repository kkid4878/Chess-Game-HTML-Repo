// player.c stub
#include <stdio.h>
#include "player.h"

static char current_player = 'W';

char player_get_current() {
    return current_player;
}

void player_switch() {
    if (current_player == 'W') {
        current_player = 'B';
    } else if (current_player == 'B') {
        current_player = 'W';
    }
//printf("Debug: Current player switched to '%c'\n", current_player);
}
