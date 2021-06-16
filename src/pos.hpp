#ifndef POS_HPP
#define POS_HPP

#include "row_col.hpp"
#include "move.hpp"

class Pos : public Row_Col {
    public:
        Pos(int r = -1, int c = -1) : Row_Col(r, c){};
        void move(Move m) {
            r += m.r;
            c += m.c;
        };
        Pos operator+(Move m) {
            return Pos(r + m.r, c + m.c);
        }
};
typedef Pos P;

#endif