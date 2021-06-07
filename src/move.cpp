#include <string>

#include "move.hpp"

namespace move{

    std::string to_string(moves_t moves) {
        std::string s;
        for (Move m : moves) {
            s += m.to_string();
            s += ", ";
        }
        s += "\n";
        return s;
    }

    std::string to_string(moves2_t moves_lists) {
        std::string s;
        for (moves_t moves : moves_lists) {
            s.append(move::to_string(moves));
        }
        s += "\n";
        return s;
    }

}