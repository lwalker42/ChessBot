#include <string>

#include "board_constants.hpp"
#include "move.hpp"

namespace move{

    std::string to_string(diffs_t diffs) {
        std::string s;
        for (Pos m : diffs) {
            s+= "(";
            s += std::to_string(m.first);
            s += ", ";
            s += std::to_string(m.second);
            s += "), ";
        }
        if (!s.empty()) s += "\n";
        return s;
    }

    std::string to_string(diffs2_t diffs_lists) {
        std::string s;
        for (diffs_t diffs : diffs_lists) {
            s.append(move::to_string(diffs));
        }
        s += "\n";
        return s;
    }

    std::string to_string(moves_t moves) {
        std::string s;
        for (Move m : moves) {
            s += m.to_string();
            s += ", ";
        }
        if (!s.empty()) s += "\n";
        return s;
    }

}