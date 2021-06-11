#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include <vector>

#include "row_col.hpp"
#include "piece.hpp"

class Move : public Row_Col {
    public:
        piece_t new_piece;
        Move(int r, int c) : Row_Col(r, c) {new_piece = __;};
        Move(int r, int c, piece_t p) : Row_Col(r, c) {new_piece = p;};
};

typedef Move M;
typedef std::vector<Move> moves_t;
typedef std::vector<moves_t> moves2_t;

namespace move {
    std::string to_string(moves_t);
    std::string to_string(moves2_t);
}

#endif