#ifndef BOARD_CONSTANTS_H
#define BOARD_CONSTANTS_H

#include"piece.h"

#define BOARD_SIZE 8

const Piece init_board[BOARD_SIZE][BOARD_SIZE] = {{r, n, b, q, k, b, n, r},
                                                  {p, p, p, p, p, p, p, p},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {P, P, P, P, P, P, P, P},
                                                  {R, N, B, Q, K, B, N, R}};

#endif