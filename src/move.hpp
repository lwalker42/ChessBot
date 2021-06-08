#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include <vector>

#include "row_col.hpp"


class Move : public Row_Col {
    public:
        Move(int r, int c) : Row_Col(r, c){};
};

typedef Move M;
typedef std::vector<Move> moves_t;
typedef std::vector<moves_t> moves2_t;

namespace move {
    std::string to_string(moves_t);
    std::string to_string(moves2_t);
}

#endif