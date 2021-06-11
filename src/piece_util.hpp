#ifndef PIECE_UTIL_HPP
#define PIECE_UTIL_HPP

#include "piece.hpp"
#include "pos.hpp"
#include "move.hpp"
#include "board_constants.hpp"


moves2_t get_piece_moves(piece_t, Special_Move = NONE);
moves2_t get_pawn_moves(piece_t, Special_Move = NONE);
#endif