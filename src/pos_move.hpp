#ifndef POS_MOVE_HPP
#define POS_MOVE_HPP

#include <utility>  //std::pair
#include <string>

#include "move.hpp"
#include "pos.hpp"

class Pos_Move : public std::pair<Pos, Move> {
    public:
        Pos pos;
        Move move;
        Pos_Move(Pos p, Move m) : std::pair<Pos, Move>(p, m), pos(first), move(second) {};
        std::string to_string() {
            return "Pos: " + pos.to_string() + ", Move: " + move.to_string();
        }
};


#endif