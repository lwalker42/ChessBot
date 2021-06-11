#ifndef UTIL_HPP
#define UTIL_HPP

#include "pos.hpp"
#include "piece.hpp"

bool on_board(int, int);
bool on_board(Pos);
bool is_pawn_first(int, int, piece_t);
bool is_pawn_first(Pos, piece_t);

#endif