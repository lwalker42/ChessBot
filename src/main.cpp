#include <iostream>
#include <string>
#include "game.hpp"


int main () {
    Game game;
    game.play_game();
    /*
    std::cout << "Depth to search to: ";
    int depth;
    std::cin >> depth;
    int num_moves = game.perft(depth);
    std::cout << "At a depth of " << depth << ", " << num_moves << " different leaf nodes were counted\n";//*/
    return 0;
}