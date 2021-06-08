#ifndef ROW_COL_HPP
#define ROW_COL_HPP

#include <utility>  //std::pair
#include <string>

class Row_Col : public std::pair<int, int> {
    public:
        int r, c;
        Row_Col(int rr, int cc) : std::pair<int, int>(rr, cc), r(first), c(second) {};
        std::string to_string() {
            return "(" + std::to_string(r) + ", " + std::to_string(c) + ")";
        }
};


#endif