#ifndef POS_MOVE_HPP
#define POS_MOVE_HPP

#include <utility>  //std::pair
#include <string>
#include <vector>

#include "move.hpp"
#include "pos.hpp"

class Pos_Move : public std::pair<Pos, Move> {
    public:
        Pos pos;
        Move move;
        Pos_Move *next = NULL;
        Pos_Move(Pos p, Move m) : std::pair<Pos, Move>(p, m), pos(first), move(second) {};
        std::string to_string() {
            return "Pos: " + pos.to_string() + ", Move: " + move.to_string();
        }
};
typedef Pos_Move PM;
typedef std::vector<Pos_Move> pos_moves_t;

namespace move {
    std::string to_string(pos_moves_t); //Implemented in move.cpp
};

#endif