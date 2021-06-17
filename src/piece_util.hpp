#ifndef PIECE_UTIL_HPP
#define PIECE_UTIL_HPP

#include "piece.hpp"
#include "move.hpp"
#include "board_constants.hpp"


diffs2_t get_piece_moves(piece_t, Special_Move = NONE);
diffs2_t get_pawn_moves(piece_t, Special_Move = NONE);
diffs2_t get_king_moves(piece_t, Special_Move = NONE);
#endif