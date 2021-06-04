#ifndef BOARD_HPP
#define BOARD_HPP

#include "board_constants.hpp"
#include "piece.hpp"

class Board {
    board_t board;
    
    public:
        Board();
        Board(Board&);
        void print_board();
        board_t get_board();
        Piece move_piece(int, int, int = -1, int = -1);
};

#endif