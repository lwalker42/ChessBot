#include <iostream>
#include "piece.h"
#include "game.h"

using namespace std;

Piece board[BOARD_SIZE][BOARD_SIZE] = {{rook, knight, bishop, queen, king, bishop, knight, rook},
                                       {pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn},
                                       {empty, empty, empty, empty, empty, empty, empty, empty},
                                       {empty, empty, empty, empty, empty, empty, empty, empty},
                                       {empty, empty, empty, empty, empty, empty, empty, empty},
                                       {empty, empty, empty, empty, empty, empty, empty, empty},
                                       {pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn},
                                       {rook, knight, bishop, queen, king, bishop, knight, rook}};


void print_board() {
    cout << endl;
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << to_string(board[i][j]);
        }
        cout << endl;
    }
}