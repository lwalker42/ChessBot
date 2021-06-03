#include <iostream>
#include "piece.h"
#include "board.h"
#include "game.h"

using namespace std; 

int main () {
    Board board;
    Board board2(board);
    Game game;
    board.print_board();
    board2.print_board();
    cout << endl;
    game.print_game();
    return 0;
}