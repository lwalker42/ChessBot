#include <iostream>
#include <string>
#include "game.hpp"

const board_t board = {{{BR,__,__,__,BK,__,__,BR},
                        {BP,__,BP,BP,BQ,BP,BB,__},
                        {BB,BN,__,__,BP,BN,BP,__},
                        {__,__,__,WP,WN,__,__,__},
                        {__,BP,__,__,WP,__,__,__},
                        {__,__,WN,__,__,WQ,__,BP},
                        {WP,WP,WP,WB,WB,WP,WP,WP},
                        {WR,__,__,__,WK,__,__,WR}
                        }};

int main () {
    Game game(false);//(board);
    game.play_game();
    /*
    std::cout << "Depth to search to: ";
    int depth;
    std::cin >> depth;
    int num_moves = game.perft(depth);
    std::cout << "At a depth of " << depth << ", " << num_moves << " different leaf nodes were counted\n";//*/
    return 0;
}