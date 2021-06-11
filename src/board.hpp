#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "board_constants.hpp"
#include "move.hpp"
#include "pos.hpp"
#include "pos_move.hpp"
#include "piece.hpp"

class Board {
    board_t board;
    
    public:
        Board();
        Board(board_t);
        Board(Board&);
        std::string to_string();
        board_t get_board();
        piece_t move_piece(int, int, int = -1, int = -1, piece_t = __);
        piece_t move_piece(int, int, Move);
        piece_t move_piece(Pos, int = -1, int = -1);
        piece_t move_piece(Pos, Move);
        piece_t move_piece(Pos_Move);

        moves_t get_moves(int, int) const;
        moves_t get_moves(Pos) const;
        moves2_t get_moves_lists(int, int) const;
        moves_t filter_moves_lists(int, int, moves2_t) const;
        moves_t filter_check(int, int, moves_t) const;
};

#endif