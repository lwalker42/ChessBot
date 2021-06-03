#include <iostream>
#include "piece.h"
#include "board.h"
#include "game.h"

using namespace std; 

int main () {
    Board board;
    board.move_piece(0, 6, 5, 7);
    board.move_piece(7, 7, 0, 1);
    board.move_piece(1, 6);
    board.print_board();
    return 0;
}