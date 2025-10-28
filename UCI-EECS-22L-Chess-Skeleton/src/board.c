// board.c stub
#include <stdio.h>
#include "board.h"

//C itself doesn't have private structs, can maybe use opaque pointer
//I dont think we need to use struct and pointers, we are given to use it as global variable (skeleton)
//we want to access the board directly, no? or am I dumb
char board[BOARD_SIZE][BOARD_SIZE];

void board_init() {
    //printf("Debug: Initializing board...\n");

    //initialize the board with empty spaces
    // '.' represents an empty square
    // removing blank spaces in the board 
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < 8; col++){
            board[row][col] = '.';
        }
    }

    board[0][0] = board[0][7] = 'R';  //set white rooks
    board[0][1] = board[0][6] = 'N';  //set white knights
    board[0][2] = board[0][5] = 'B';  //set white bishops
    board[0][3] = 'Q';   //set white queen
    board[0][4] = 'K';   //set white king
            
    //set white pawns
    for (int col = 0; col < 8; col++) {
        board[1][col] = 'P';  
    }

    board[7][0] = board[7][7] = 'r';  //set black rooks
    board[7][1] = board[7][6] = 'n';  //set black knights   
    board[7][2] = board[7][5] = 'b';  //set black bishops
    board[7][3] = 'q';   //set black queen
    board[7][4] = 'k';   //set black king

    //set black pawns
    for (int col = 0; col < 8; col++) {
        board[6][col] = 'p';  
    }

    /*printf("Debug: Board initialized.\n");
    board_print(); // Print the board after initialization*/
}

char board_get(int row, int col) {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        //printf("Debug: board_get(%d, %d) - Out of bounds, returning '.'\n", row, col);
        return '.'; // Return empty square if out of bounds
    }
    //printf("Debug: board_get(%d, %d) = '%c'\n", row, col, board[row][col]);
    return board[row][col];
}

void board_set(int row, int col, char piece) {
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        //printf("Debug: board_set(%d, %d, '%c')\n", row, col, piece);
        board[row][col] = piece;
    } /*else {
        //printf("Debug: board_set(%d, %d, '%c') - Out of bounds, no update performed\n", row, col, piece);
    }*/
}

/*void board_print() {
    printf("Debug: Current board state:\n");
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}*/