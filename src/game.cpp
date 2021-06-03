#include <iostream>
#include "piece.h"
#include "game.h"

using namespace std;

Piece board[BOARD_SIZE][BOARD_SIZE] = {{r, n, b, q, k, b, n, r},
                                       {p, p, p, p, p, p, p, p},
                                       {_, _, _, _, _, _, _, _},
                                       {_, _, _, _, _, _, _, _},
                                       {_, _, _, _, _, _, _, _},
                                       {_, _, _, _, _, _, _, _},
                                       {P, P, P, P, P, P, P, P},
                                       {R, N, B, Q, K, B, N, R}};


void print_board() {
    cout << endl;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << to_char(board[i][j]);
        }
        cout << endl;
    }
}