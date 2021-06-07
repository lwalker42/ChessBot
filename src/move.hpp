#ifndef MOVE_HPP
#define MOVE_HPP

#include <utility>
#include <string>
#include <vector>

//(change in row, change in col) i.e. (delta_y, delta_x)

class Move : public std::pair<int, int> {
    public:
        int r, c;
        Move(int rr, int cc) : std::pair<int, int>(rr, cc), r(first), c(second) {};
        std::string to_string() {
            return "(" + std::to_string(r) + ", " + std::to_string(c) + ")";
        }
};
typedef Move M;
typedef std::vector<Move> moves_t;
typedef std::vector<moves_t> moves2_t;

namespace move {
    std::string to_string(moves_t);
    std::string to_string(moves2_t);
}

#endif