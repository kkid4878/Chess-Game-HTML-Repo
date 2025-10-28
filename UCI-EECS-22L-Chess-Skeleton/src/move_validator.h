// move_validator.h stub
#ifndef MOVE_VALIDATOR_H
#define MOVE_VALIDATOR_H

#include <stdbool.h>
#include "io.h"

//declaration of different validation functions
bool is_valid_move(Move move, char player);
bool validate_pawn_move(Move move, char player);
bool validate_rook_move(Move move);
bool validate_knight_move(Move move);
bool validate_bishop_move(Move move);
bool validate_queen_move(Move move);
bool validate_king_move(Move move);


#endif
