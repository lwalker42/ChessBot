#include <iostream>
#include "piece.h"
#include "board.h"

using namespace std;

const Piece init_board[BOARD_SIZE][BOARD_SIZE] = {{r, n, b, q, k, b, n, r},
                                                  {p, p, p, p, p, p, p, p},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {_, _, _, _, _, _, _, _},
                                                  {P, P, P, P, P, P, P, P},
                                                  {R, N, B, Q, K, B, N, R}};


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
    cout << endl;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << to_char(board[i][j]);
        }
        cout << endl;
    }
}