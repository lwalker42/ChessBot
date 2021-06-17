#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "board_constants.hpp"
#include "move.hpp"
#include "piece.hpp"

class Board {
    board_t board;

    bool check_for_piece(Pos, std::vector<piece_t>, diffs2_t) const;
    
    public:
        Board();
        Board(board_t);
        Board(Board&);
        piece_t operator[](Pos) const;
        std::string to_string() const;
        board_t get_board() const;
        piece_t move_piece(int, int, int = -1, int = -1, Special_Move = NONE, piece_t = __, piece_t = __);  //deprecated
        piece_t move_piece(const Move&);
        piece_t unmove_piece(int, int, int = -1, int = -1, Special_Move = NONE, piece_t = __, piece_t = __);//deprecated
        piece_t unmove_piece(const Move&);

        moves_t get_moves(int, int, Special_Move = NONE, Pos = {-1, -1}) const;
        moves_t get_moves(Pos, Special_Move = NONE, Pos = {-1, -1}) const;
        diffs2_t get_moves_lists(int, int, Special_Move = NONE) const;
        moves_t filter_moves_lists(int, int, diffs2_t, Special_Move = NONE, Pos = {-1, -1}) const;

        Pos get_king_pos(bool) const;
        bool in_check(bool) const;
};

#endif