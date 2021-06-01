#ifndef GAME_H
#define GAME_H

#include "piece.h"

using namespace std;

#define BOARD_SIZE 8


extern Piece board[BOARD_SIZE][BOARD_SIZE]; 

void print_board();

#endif