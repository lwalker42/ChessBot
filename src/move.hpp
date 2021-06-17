#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include <vector>
#include <functional>

#include "type_defs.hpp"
#include "piece.hpp"

class Move {
    public:
        Pos from, to;
        piece_t captured, promotion;
        Special_Move sm;
        int game_flags = 0;
        Move(Pos f, Pos t, Special_Move s = NONE, piece_t c = __, piece_t p = __) : from(f), to(t), sm(s), captured(c), promotion(p) {};
        Move(const Move &m) : from(m.from), to(m.to), sm(m.sm), captured(m.captured), promotion(m.promotion), game_flags(m.game_flags) {};
        std::string to_string() const {
            return "From ("+std::to_string(from.first)+", "+std::to_string(from.second)+")"
                 + ", to ("+std::to_string(to.first)+", "+std::to_string(to.second)+")"
                 + ((captured == __) ? "" : ", capturing " + to_char(captured))
                 + ((promotion == __) ? "" : ", promoting to " + to_char(promotion));
        }
};

typedef std::vector<Move> moves_t;

namespace move {
    std::string to_string(diffs_t);
    std::string to_string(diffs2_t);
    std::string to_string(moves_t);
};

#endif