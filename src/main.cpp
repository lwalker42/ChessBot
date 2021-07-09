#include <iostream>
#include <string>
#include "game.hpp"
#include "player/player.hpp"
#include "timer.hpp"
#include "test_boards.hpp"


int main (int argc, char *argv[]) {
    int white_player = HUMAN_PLAYER;
    int black_player = HUMAN_PLAYER;
    if (argc == 3) {
        white_player = std::stoi(argv[1]);
        black_player = std::stoi(argv[2]);
    }
    Game game(white_player, black_player);
    //Game game(init_board);
    //Game game(board2);
    //Game game(board3, WHITE, false, false, false, false);
    //Game game(board4, WHITE, false, false, true, true);
    //Game game(HUMAN_PLAYER, CPU_PLAYER, board5, WHITE, true, true, false, false);
    game.play_game();
    /*
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