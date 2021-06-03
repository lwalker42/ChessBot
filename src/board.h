#ifndef GAME_H
#define GAME_H

#include "piece.h"

#define BOARD_SIZE 8



class Board {
    public:
    Piece board[BOARD_SIZE][BOARD_SIZE];
    
    public:
        Board();
        Board(Board&);
        void print_board();
};

#endif