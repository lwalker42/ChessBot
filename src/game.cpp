#include <iostream>
#include "game.hpp"

Game::Game() {
    Board board;
    turn = true;
    white_queenside = true;
    white_kingside = true;
    black_queenside = true;
    black_kingside = true;
    
}

void Game::print_game() {
    std::cout << board.to_string();
    std::cout << (turn ? "White's turn\n" : "Black's turn\n");
}