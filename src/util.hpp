#ifndef UTIL_HPP
#define UTIL_HPP

#include "board_constants.hpp"
#include "type_defs.hpp"
#include "piece.hpp"

inline bool on_board(int r, int c) {
    return (0 <= r && r < BOARD_SIZE && 0 <= c && c < BOARD_SIZE);
}
inline bool on_board(Pos p) {
    return (0 <= p.first && p.first < BOARD_SIZE && 0 <= p.second && p.second < BOARD_SIZE);
}
bool is_pawn_first(int, int, piece_t = WP);
bool is_pawn_first(Pos, piece_t = WP);
bool is_pawn_promotion(int, int, piece_t = WP);
bool is_pawn_promotion(Pos, piece_t = WP);
bool is_kingside(int, int, piece_t = WR);
bool is_kingside(Pos, piece_t = WR);
bool is_queenside(int, int, piece_t = WR);
bool is_queenside(Pos, piece_t = WR);
Pos operator+(const Pos &, const Pos &);


#endif