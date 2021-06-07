#include <string>

#include "move.hpp"


std::string to_string(moves_t moves) {
    std::string s;
    for (Move m : moves) {
        s += m.to_string();
        s += ", ";
    }
    return s;
}

std::string to_string(moves2_t moves_lists) {
    std::string s;
    for (moves_t moves : moves_lists) {
        s.append(to_string(moves));
    }
    return s;
}
