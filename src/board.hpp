#ifndef BOARD_HPP
#define BOARD_HPP

#include "board_constants.hpp"
#include "move.hpp"
#include "piece.hpp"

class Board {
    board_t board;
    
    public:
        Board();
        Board(Board&);
        void print_board();
        board_t get_board();
        Piece move_piece(int, int, int = -1, int = -1);
        Piece move_piece(int, int, Move);
        moves_t get_moves(int, int);
        moves2_t get_moves_lists(int, int);
        moves_t filter_moves_lists(int, int, moves2_t);
        moves_t filter_check(int, int, moves_t);
};

#endif