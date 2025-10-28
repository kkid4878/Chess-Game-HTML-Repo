// move_validator.c stub
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "move_validator.h"
#include "board.h"

// Helper: checks if move is in straight line
/*### 3.5 Move Validator Module (`move_validator.c/h`)
- `bool is_valid_move(Move move, char player);`
  - Returns `true` if the move is legal based on the piece type.
  - Only basic rules: no castling, no en passant, no promotion.
  - Moves must follow piece-specific motion:
    - Pawn: forward, no diagonal capture
    - Rook: straight lines
    - Bishop: diagonals
    - Knight: `L` shape
    - Queen: straight + diagonal
    - King: one square in anyar player);`
  - Returns `true` if the player's king is under attack.
- `bool is_checkmate(char player);`
  - Returns `true` if the player is in check and has no legal moves.
- Implementation may simulate moves and undo them.*/



static bool is_straight(Move m) {
    //Check if move is in same row or column
    return (m.from_row == m.to_row || m.from_col == m.to_col);
    
    
}

// Helper: checks if move is diagonal
static bool is_diagonal(Move m) {
    //Check if move is in same row or column
    return (abs(m.from_row - m.to_row) == abs(m.from_col - m.to_col));
    
}

//if valid move debug statements
bool is_valid_move(Move move, char current_player) {
    //printf("Debug: Entering is_valid_move for player %c\n", current_player);
    //printf("Debug: Validating move from (%d, %d) to (%d, %d) for player %c\n",
    //       move.from_row, move.from_col, move.to_row, move.to_col, current_player);

    char piece = board_get(move.from_row, move.from_col);
    //printf("Debug: Piece at source (%d, %d) is '%c'\n", move.from_row, move.from_col, piece);

    // Empty source
    if (piece == '.') {
        //printf("Debug: Source square is empty.\n");
        return false;
    }

    // Check piece belongs to player
    if (current_player == 'W' && !isupper(piece)) {
        //printf("Debug: Piece does not belong to player W.\n");
        return false;
    }
    if (current_player == 'B' && !islower(piece)) {
        //printf("Debug: Piece does not belong to player B.\n");
        return false;
    }

    // Normalize piece to lowercase for logic
    char normalized = tolower(piece);
    //printf("Debug: Normalized piece is '%c'\n", normalized); 

    switch (normalized) { 
        case 'p':
            return validate_pawn_move(move, current_player);
        case 'r':
            return validate_rook_move(move);
        case 'n':
            return validate_knight_move(move);
        case 'b':
            return validate_bishop_move(move);
        case 'q':
            return validate_queen_move(move);
        case 'k':
            return validate_king_move(move);
        default:
            return false;
    }
    //printf("Debug: Invalid piece type '%c'.\n", normalized);
}

bool validate_pawn_move(Move move, char current_player) {
    int direction = (current_player == 'W') ? 1 : -1; // White moves up (-1), Black moves down (+1)
    int start_row = (current_player == 'W') ? 1 : 6; // Starting row for pawns

    int row_diff = move.to_row - move.from_row; //can only move forward so row_diff must be absolute
    int col_diff = abs(move.to_col - move.from_col);

    char target = board_get(move.to_row, move.to_col);

    //printf("Debug: Pawn move - direction=%d, start_row=%d, row_diff=%d, col_diff=%d, target='%c'\n",
    //       direction, start_row, row_diff, col_diff, target);

    // Moving forward
    if (col_diff == 0) {
        //One square forward
        if (row_diff == direction && target == '.') {
            //printf("Debug: Pawn moves one square forward.\n");
            return true;
        }
        //Two squares from starting position
        if (move.from_row == start_row &&
            row_diff == 2 * direction &&
            target == '.' &&
            board_get(move.from_row + direction, move.from_col) == '.') {
            //printf("Debug: Pawn moves two squares forward from starting position.\n");
            return true;
        }
    }

    // Capturing diagonally
    if (col_diff == 1 && row_diff == direction) {
        if (target != '.') {
            if (current_player == 'W' && islower(target)) {
                //printf("Debug: Pawn captures diagonally.\n");
                return true;
            }
            if (current_player == 'B' && isupper(target)) {
                //printf("Debug: Pawn captures diagonally.\n");
                return true;
            }
        } else {
            //printf("Debug: Pawn attempted diagonal capture, but target is empty.\n");
        }
    }

    //printf("Debug: Pawn move is invalid.\n");
    return false;
}

/* bool validate_rook_move(Move move) {
    int row_diff = abs(move.to_row - move.from_row);
    int col_diff = abs(move.to_col - move.from_col);
    
    char target = board_get(move.to_row, move.to_col);
    char piece = board_get(move.from_row, move.from_col);

    // Check if the move is straight (same row or column)
    if (is_straight(move)) {
        // Check if the path is clear (no pieces in 1between)
        for (int i = 1; i < abs(row_diff + col_diff); i++) {
            int row_step = (row_diff == 0) ? 0 : (row_diff > 0 ? i : -i); // checks if 
            int col_step = (col_diff == 0) ? 0 : (col_diff > 0 ? i : -i);
            if (board_get(move.from_row + row_step, move.from_col + col_step) != ' ') {
                return false; // Path is blocked
            }
        }
        // Check if the target square is empty or occupied by an opponent's piece
        if (target == '.' || (islower(target) && isupper(piece)) || (isupper(target) && islower(piece))) {
            return true;
        }
    }
    return false;
}*/

bool validate_rook_move(Move move) {
    //Check if move is in straight line
    if (is_straight(move)){

		//Moving horizontally & checking if path is clear
		if (move.from_row == move.to_row) {
			int row_step;
			if (move.to_col > move.from_col)
				row_step = 1;
			else
				row_step = -1;
			for (int col = move.from_col + row_step; col != move.to_col; col += row_step) {
				if (board_get(move.from_row, col) != '.') return false;
			}
		}
		

		//Moving vertically & checking if path is clear
		else if (move.from_col == move.to_col) {
			int col_step;
			if (move.to_row > move.from_row)
				col_step = 1;
			else
				col_step = -1;
			for (int row = move.from_row + col_step; row != move.to_row; row += col_step) {
				if (board_get(row, move.from_col) != '.') return false;
			}
		}
		//Check if target square is empty or occupied by enemy piece
		char target = board_get(move.to_row, move.to_col);
		char piece = board_get(move.from_row, move.from_col);
        
        if (target == '.' || (islower(target) && isupper(piece)) || (isupper(target) && islower(piece))) {
            return true;
        }
	}
   
    return false;    
}


 bool validate_knight_move(Move move) {
    /*
    Knight moves in L shape: 2 squares up/down and 1 square left/right
                            or 1 square up/down and 2 squares left/right.
    */
    
    int row_diff = abs(move.to_row - move.from_row);
    int col_diff = abs(move.to_col - move.from_col);

    if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)) {
        char target = board_get(move.to_row, move.to_col); 
        char piece = board_get(move.from_row, move.from_col);
        // Check if target square is empty or occupied by enemy piece
        if (target == '.' || (islower(target) && isupper(piece)) || (isupper(target) && islower(piece))) {
            return true;
        }
    }
    return false;
}

 bool validate_bishop_move(Move move){
    //Check if move is diagonal
    if (is_diagonal(move)){

        int row_step, col_step;
        if (move.to_row > move.from_row)
            row_step = 1;
        else
            row_step = -1;
        if (move.to_col > move.from_col)
            col_step = 1;
        else
            col_step = -1;
        
        
        int row = move.from_row + row_step;
        int col = move.from_col + col_step;
        
        //Plus/Minus one column and row step at the same time to move diagonally
        //Check if path is clear
        while (row != move.to_row && col != move.to_col) {  
            if (board_get(row, col) != '.')
                return false;
            row += row_step;
            col += col_step;
        }
        
        //Check if target square is empty or occupied by enemy piece
        char target = board_get(move.to_row, move.to_col);
        char piece = board_get(move.from_row, move.from_col);
        
        if (target == '.' || (islower(target) && isupper(piece)) || (isupper(target) && islower(piece))) {
            return true;
        }
    }
    return false;
}

 bool validate_queen_move(Move move){
    //Uses rook and bishop functions to check if valid diagonal and straight spaces are open
    //Already implement rook and bishop move validation, we can just call them
    if (validate_rook_move(move) || 
        validate_bishop_move(move)) {
        return true;
    }
    return false;
}

 bool validate_king_move(Move move){
    /*
    King can move one square in any direction.
    row = |to_row - from_row| = 1 && col = |to_col - from_col| = 0
    col = |to_col - from_col| = 1 && row = |to_row - from_row| = 0
    row = |to_row - from_row| = 1 && col = |to_col - from_col| = 1

    what about if out of board? where would we put bound check?
    */

    int row_diff = abs(move.to_row - move.from_row);
    int col_diff = abs(move.to_col - move.from_col);

    if ((row_diff == 1 && col_diff == 0) || (col_diff == 1 && row_diff == 0) || (row_diff == 1 && col_diff == 1)) {
        char target = board_get(move.to_row, move.to_col);
        char piece = board_get(move.from_row, move.from_col);
        // Check if target square is empty or occupied by enemy piece
        if (target == '.' || (islower(target) && isupper(piece)) || (isupper(target) && islower(piece))) {
            return true;
        }
    }
    return false;
}