#ifndef POS_MOVE_HPP
#define POS_MOVE_HPP

#include <string>
#include <vector>

#include "move.hpp"
#include "pos.hpp"

class Pos_Move {
    public:
        Pos pos;
        Move move;
        Pos_Move *next = NULL;
        Pos_Move(Pos p, Move m, Pos_Move* n = NULL) : pos(p), move(m), next(n) {};
        Pos_Move(int r, int c, Move m, Pos_Move* n = NULL) : move(m), next(n) {Pos *p = new Pos(r, c); pos = *p;}
        Pos_Move(const Pos_Move &pm) : Pos_Move(pm.pos, pm.move, pm.next) {};
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