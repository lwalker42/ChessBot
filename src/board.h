#ifndef GAME_H
#define GAME_H

#include "piece.h"

using namespace std;

#define BOARD_SIZE 8



class Board {
    Piece board[BOARD_SIZE][BOARD_SIZE];
    
    public:
        Board();
        void print_board();
};

#endif