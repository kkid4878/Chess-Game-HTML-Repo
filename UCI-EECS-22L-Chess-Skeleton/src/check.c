// check.c stub
#include <ctype.h>
#include "check.h"
#include "board.h"
#include "move_validator.h"
#include "io.h"

// Stub: Checks if the player's piece is the enemy's or the players
static bool is_enemy(char piece, char player) {
    if (piece == '.')
     return false;

    if (player == 'W') 
        return islower(piece);
    else if (player == 'B')
        return isupper(piece);
        
    return false;
}


// Stub: Determines if the given player is in check.
bool is_in_check(char player) {
     /*
    Determine the king piece based on the player ('K' or 'k').
    Get the position of the king.
    Check if the king is in check by checking the board.
    For each piece on the board, check it belongs to the enemy player.
        If yes, check if it can attack the king.
        If yes, return true.
    else return false.  
    */
    int king_row, king_col;
    char king_piece;

    //Determine the king piece based on the player
    if (player == 'W') {
        king_piece = 'K';
    } else if (player == 'B') {
        king_piece = 'k';
    }
   
    //Get the position of the king
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (board[row][col] == king_piece) {
                king_row = row;
                king_col = col;
                break;
            }
        }
    }

    //Check if the king is in check by checking the board
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            char board_piece = board[row][col];

            if (board_piece == '.') continue; //skip empty squares
            
            if (is_enemy(board_piece, player)) {    //check it belongs to the enemy
                Move attack;
                attack.from_row = row;
                attack.from_col = col;
                attack.to_row = king_row;
                attack.to_col = king_col;
                // Enemy player is the opposite of 'player'
                char enemy_player = (player == 'W') ? 'B' : 'W';
                if (is_valid_move(attack, enemy_player)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Stub: Checks if a given players is in checkmate
bool is_checkmate(char player) { 
    if (!is_in_check(player)) {
        return false; // Not in check, so not checkmate
    }

    // Find the king's position
    int king_row = -1, king_col = -1;
    char king_piece = (player == 'W') ? 'K' : 'k';
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (board[row][col] == king_piece) {
                king_row = row;
                king_col = col;
                break;
            }
        }
    }

    // Try all possible king moves
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int new_row = king_row + dr;
            int new_col = king_col + dc;
            if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
                Move move;
                move.from_row = king_row;
                move.from_col = king_col;
                move.to_row = new_row;
                move.to_col = new_col;
                move.piece = king_piece;
                if (is_valid_move(move, player)) {
                    // Simulate the move
                    char temp = board[new_row][new_col];
                    board[king_row][king_col] = '.';
                    board[new_row][new_col] = king_piece;
                    bool still_in_check = is_in_check(player);
                    // Undo the move
                    board[king_row][king_col] = king_piece;
                    board[new_row][new_col] = temp;
                    if (!still_in_check) {
                        return false; // King can escape
                    }
                }
            }
        }
    }

    // Try all possible moves for all friendly pieces to block/capture
    for (int from_row = 0; from_row < 8; from_row++) {
        for (int from_col = 0; from_col < 8; from_col++) {
            char piece = board[from_row][from_col];
            // Skip empty squares and the king itself
            if (piece == '.' || piece == king_piece) continue;
            // Check if piece belongs to the player
            if ((player == 'W' && isupper(piece)) || (player == 'B' && islower(piece))) {
                for (int to_row = 0; to_row < 8; to_row++) {
                    for (int to_col = 0; to_col < 8; to_col++) {
                        if (from_row == to_row && from_col == to_col) continue;
                        Move move;
                        move.from_row = from_row;
                        move.from_col = from_col;
                        move.to_row = to_row;
                        move.to_col = to_col;
                        move.piece = piece;
                        if (is_valid_move(move, player)) {
                            // Simulate the move
                            char temp = board[to_row][to_col];
                            board[from_row][from_col] = '.';
                            board[to_row][to_col] = piece;
                            bool still_in_check = is_in_check(player);
                            // Undo the move
                            board[from_row][from_col] = piece;
                            board[to_row][to_col] = temp;
                            if (!still_in_check) {
                                return false; // A piece can block/capture
                            }
                        }
                    }
                }
            }
        }
    }

    // No valid moves, checkmate
    return true;
}

