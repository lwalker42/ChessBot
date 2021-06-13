#ifndef UTIL_HPP
#define UTIL_HPP

#include "pos.hpp"
#include "piece.hpp"

bool on_board(int, int);
bool on_board(Pos);
bool is_pawn_first(int, int, piece_t = WP);
bool is_pawn_first(Pos, piece_t = WP);
bool is_pawn_promotion(int, int, piece_t = WP);
bool is_pawn_promotion(Pos, piece_t = WP);
bool is_kingside(int, int, piece_t = WR);
bool is_kingside(Pos, piece_t = WR);
bool is_queenside(int, int, piece_t = WR);
bool is_queenside(Pos, piece_t = WR);

#endif