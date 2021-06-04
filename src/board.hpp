#ifndef BOARD_HPP
#define BOARD_HPP

#include "board_constants.hpp"
#include "piece.hpp"

class Board {
    Piece board[BOARD_SIZE][BOARD_SIZE];
    
    public:
        Board();
        Board(Board&);
        void print_board();
        Piece move_piece(int, int, int = -1, int = -1);
};

#endif