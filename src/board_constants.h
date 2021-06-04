#ifndef BOARD_CONSTANTS_H
#define BOARD_CONSTANTS_H

#include "piece.h"
#include "move.h"

#define BOARD_SIZE 8

const Piece init_board[BOARD_SIZE][BOARD_SIZE] = {{r, n, b, q, k, b, n, r},
                                                  {p, p, p, p, p, p, p, p},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {P, P, P, P, P, P, P, P},
                                                  {R, N, B, Q, K, B, N, R}};

const Move diag_moves[] = {Move(1, 1), Move(2, 2), Move(3, 3), Move(4, 4),
                           Move(5, 5), Move(6, 6), Move(7, 7),
                           Move(-1, -1), Move(-2, -2), Move(-3, -3), Move(-4, -4),
                           Move(-5, -5), Move(-6, -6), Move(-7, -7),
                           Move(1, -1), Move(2, -2), Move(3, -3), Move(4, -4),
                           Move(5, -5), Move(6, -6), Move(7, -7),
                           Move(-1, 1), Move(-2, 2), Move(-3, 3), Move(-4, 4),
                           Move(-5, 5), Move(-6, 6), Move(-7, 7)
                          };

const Move ortho_moves[] = {Move(1, 0), Move(2, 0), Move(3, 0), Move(4, 0), 
                            Move(5, 0), Move(6, 0), Move(7, 0),
                            Move(-1, 0), Move(-2, 0), Move(-3, 0), Move(-4, 0), 
                            Move(-5, 0), Move(-6, 0), Move(-7, 0),
                            Move(0, 1), Move(0, 2), Move(0, 3), Move(0, 4),
                            Move(0, 5), Move(0, 6), Move(0, 7),
                            Move(0, -1), Move(0, -2), Move(0, -3), Move(0, -4),
                            Move(0, -5), Move(0, -6), Move(0, -7)
                           };

const Move king_moves[] = {Move(1, 0), Move(1, 1), Move(0, 1), Move(-1, 1), 
                           Move(-1, 0), Move(-1, -1), Move(0, -1), Move(1, -1)
                          };

const Move knight_moves[] = {Move(1, 2), Move(1, -2), Move(-1, 2), Move(-1, 2), 
                             Move(2, 1), Move(2, -1), Move(-2, 1), Move(-2, -1)
                            };

const Move pawn_first_moves[] = {Move(0, -1), Move(0, -2)};
const Move pawn_moves[] = {Move(0, -1)};
const Move pawn_capture_moves[] = {Move(1, -1), Move(-1, -1)};


#endif