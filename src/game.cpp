#include <iostream>
#include "piece.h"
#include "game.h"

using namespace std;


void printBoard() {
    cout << endl;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << toString(board[i][j]);
        }
        cout << endl;
    }
}