#ifndef POS_HPP
#define POS_HPP

#include "row_col.hpp"

class Pos : public Row_Col {
    public:
        Pos(int r, int c) : Row_Col(r, c){};
};

#endif