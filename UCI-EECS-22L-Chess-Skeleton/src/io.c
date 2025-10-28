// io.c stub
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "io.h"
#include "move_validator.h"
#include "player.h"

static int file_to_col(char file)
{
    if ( file < 'a' || file > 'h')
    {
        return -1;
    }
    int colume_index = (int)(file - 'a');
    return colume_index;
}

static int rank_to_row(char rank)
{
    if (rank < '1' || rank > '8')
    {
        return -1;
    }
    int row_index = (int)(rank - '1');
    return row_index;
}

bool io_get_move(Move* move)
{
    char input[10] = {0};
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) != 5)
    {
        return false;
    }
    if (file_to_col(input[0]) == -1 || 
        rank_to_row(input[1]) == -1 || 
        file_to_col(input[3]) == -1 || 
        rank_to_row(input[4]) == -1)
    {
        return false;
    }
    move->from_col = file_to_col(input[0]);
    move->from_row = rank_to_row(input[1]);
    move->to_col = file_to_col(input[3]);
    move->to_row = rank_to_row(input[4]);

    printf("Move: from (%d, %d) to (%d, %d)\n", move->from_row, move->from_col, move->to_row, move->to_col);

    
    if (is_valid_move(*move, player_get_current()))
    {   
        //printf("This is_valid_move is from io.c^^^ \n");
        return true;
    }
    return false;
}


//adding comment to update the commit history, the change is the the user EinVehicle
//student Id is 38601395, Yifei Wang