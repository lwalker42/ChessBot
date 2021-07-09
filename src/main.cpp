#include <iostream>
#include <string>
#include "game.hpp"
#include "player.hpp"
#include "timer.hpp"
#include "test_boards.hpp"


int main () {
    //Game game(init_board);
    //Game game(board2);
    //Game game(board3, WHITE, false, false, false, false);
    //Game game(board4, WHITE, false, false, true, true);
    Game game(HUMAN_PLAYER, CPU_PLAYER, board5, WHITE, true, true, false, false);
    //game.play_game();
    ///*
    std::cout << "Depth to search to: ";
    int depth;
    std::cin >> depth;
    start_time();
    int num_moves = game.perft(depth);
    end_time();
    std::cout << "Time elapsed: " << elapsed << "\n";
    std::cout << "At a depth of " << depth << ", " << num_moves << " different leaf nodes were counted\n";//*/
    return 0;
}