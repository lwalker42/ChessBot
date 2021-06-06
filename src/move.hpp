#ifndef MOVE_HPP
#define MOVE_HPP

#include <utility>
#include <string>

class Move : public std::pair<int, int> {
    public:
    int r, c;
    Move(int rr, int cc) : std::pair<int, int>(rr, cc), r(first), c(second) {};
    std::string to_string() {
        std::string s;
        s.append("(").append(std::to_string(r)).append(", ").append(std::to_string(c)).append(")");
        return s;
    }
};
typedef Move M;

#endif