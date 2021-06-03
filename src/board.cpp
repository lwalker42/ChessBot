#include <iostream>
#include "piece.h"
#include "board.h"

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