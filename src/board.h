#ifndef BOARD_H
#define BOARD_H

#include "board_constants.h"
#include "piece.h"



class Board {
    Piece board[BOARD_SIZE][BOARD_SIZE];
    
    public:
        Board();
        Board(Board&);
        void print_board();
        Piece move_piece(int, int, int = -1, int = -1);
};

#endif