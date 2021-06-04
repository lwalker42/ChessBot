#include <iostream>
#include "piece.h"
#include "board_constants.h"
#include "board.h"
#include "util.h"

using namespace std;


Board::Board() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = init_board[i][j];
        }
    }
}

Board::Board(Board &b) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = b.board[i][j];
        }
    }
}

void Board::print_board() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << to_char(board[i][j]);
        }
        cout << endl;
    }
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