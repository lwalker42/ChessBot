#include <string>

#include "piece.hpp"
#include "move.hpp"
#include "board_constants.hpp"
#include "board.hpp"
#include "util.hpp"


Board::Board() {
    board = init_board;
}

Board::Board(board_t b) {
    board = b;
}

Board::Board(Board &b) {
    board = b.board;
}

std::string Board::to_string() {
    std::string str;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            str += to_char(board[i][j]);
        }
        str += "\n";
    }
    return str;
}

board_t Board::get_board() {
    return board;
}

piece_t Board::move_piece(int r1, int c1, int r2, int c2) {
    if (!on_board(r1, c1)) return __;

    piece_t p = board[r1][c1];
    if (p == __) return p;
    board[r1][c1] = __;
    if (on_board(r2, c2)) {
        board[r2][c2] = p;
    }
    return p;
}

piece_t Board::move_piece(int r, int c, Move m) {
    return move_piece(r, c, r + m.r, c + m.c);
}



moves_t Board::get_moves(int r, int c) {
    moves_t moves;
    moves2_t m_list = get_moves_lists(r, c);
    for (moves_t m : m_list) {
        moves.insert(moves.end(), m.begin(), m.end());
    }
    return moves;
}

moves2_t Board::get_moves_lists(int r, int c) {
    if (!on_board(r, c)) return {};
    return get_piece_moves(board[r][c]);
}

moves_t Board::filter_moves_lists(int r1, int c1, moves2_t moves_list) {

}