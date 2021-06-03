#include <iostream>
#include "piece.h"
#include "board.h"

using namespace std; 

int main () {
    Board board;
    Board board2(board);
    board.print_board();
    board2.print_board();
    return 0;
}