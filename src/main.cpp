#include <iostream>
#include "piece.hpp"
#include "board.hpp"
#include "game.hpp"


int main () {
    Board board;
    board.move_piece(0, 6, 5, 7);
    board.move_piece(7, 7, 0, 1);
    board.move_piece(1, 6);
    std::cout << board.to_string();
    return 0;
}