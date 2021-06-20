#ifndef TYPE_DEFS_HPP
#define TYPE_DEFS_HPP

#include <utility>  //std::pair
#include <array>
#include <vector>

#include "piece.hpp"

#define BOARD_SIZE 8

enum Special_Move {
    NONE,
    MOVE_ONLY,
    PAWN_STARTING,
    EN_PASSANT,
    CAPTURE_ONLY,
    PROMOTION,
    KINGSIDE,
    QUEENSIDE
};

typedef std::array<std::array<piece_t, BOARD_SIZE>, BOARD_SIZE> board_t;
typedef std::vector<piece_t> pieces_t;

typedef std::pair<int, int> Pos;
typedef Pos P;
typedef std::vector<Pos> diffs_t;
typedef diffs_t pos_t;
typedef std::vector<diffs_t> diffs2_t;

#endif