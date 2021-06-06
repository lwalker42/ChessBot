#include <iostream>
#include "piece.hpp"
#include "move.hpp"
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

Piece Board::move_piece(int r1, int c1, Move m) {
    return move_piece(r1, c1, r1 + m.r, c1 + m.c);
}

moves_t Board::get_moves(int r1, int r2) {
    moves_t moves;
    moves2_t m_list = get_moves_lists(r1, r2);
    for (moves_t m : m_list) {
        moves.insert(moves.end(), m.begin(), m.end());
    }
    return moves;
}

moves2_t Board::get_moves_lists(int r1, int c1) {
    if (!on_board(r1, c1)) return {};
    switch(board[r1][c1]) {
        case K:
        case k:
            return king_moves;
        case Q:
        case q:
            return queen_moves;
        case R:
        case r:
            return rook_moves;
        case B:
        case b:
            return bishop_moves;
        case N:
        case n:
            return knight_moves;
        case P:
        case p:
            return pawn_moves;
        default:
            return {};
    }
}

moves_t Board::filter_moves_lists(int r1, int c1, moves2_t moves_list) {

}