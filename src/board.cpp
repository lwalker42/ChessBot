#include <iostream>
#include "piece.hpp"
#include "board_constants.hpp"
#include "board.hpp"
#include "util.hpp"


Board::Board() {
    board = init_board;
}

Board::Board(Board &b) {
    board = b.board;
}

void Board::print_board() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            std::cout << to_char(board[i][j]);
        }
        std::cout << std::endl;
    }
}

board_t Board::get_board() {
    return board;
}

Piece Board::move_piece(int r1, int c1, int r2, int c2) {
    if (!on_board(r1, c1)) return _;

    Piece p = board[r1][c1];
    if (p == _) return _;
    board[r1][c1] = _;
    if (on_board(r2, c2)) {
        board[r2][c2] = p;
    }
    return p;
}