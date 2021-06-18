#include <iostream>
#include <string>
#include "game.hpp"

const board_t board2= {{{BR,__,__,__,BK,__,__,BR},
                        {BP,__,BP,BP,BQ,BP,BB,__},
                        {BB,BN,__,__,BP,BN,BP,__},
                        {__,__,__,WP,WN,__,__,__},
                        {__,BP,__,__,WP,__,__,__},
                        {__,__,WN,__,__,WQ,__,BP},
                        {WP,WP,WP,WB,WB,WP,WP,WP},
                        {WR,__,__,__,WK,__,__,WR}
                        }};

const board_t board3= {{{__,__,__,__,__,__,__,__},
                        {__,__,BP,__,__,__,__,__},
                        {__,__,__,BP,__,__,__,__},
                        {WK,WP,__,__,__,__,__,BR},
                        {__,WR,__,__,__,BP,__,BK},
                        {__,__,__,__,__,__,__,__},
                        {__,__,__,__,WP,__,WP,__},
                        {__,__,__,__,__,__,__,__},
                        }};

const board_t board5= {{{BR,BN,BB,BQ,__,BK,__,BR},
                        {BP,BP,__,WP,BB,BP,BP,BP},
                        {__,__,BP,__,__,__,__,__},
                        {__,__,__,__,__,__,__,__},
                        {__,__,WB,__,__,__,__,__},
                        {__,__,__,__,__,__,__,__},
                        {WP,WP,WP,__,WN,BN,WP,WP},
                        {WR,WN,WB,WQ,WK,__,__,WR}
                        }};

int main () {
    //Game game;
    Game game(board2);
    //Game game(board3);
    //Game game(board5, WHITE, true, true, false, false);
    //game.play_game();
    ///*
    std::cout << "Depth to search to: ";
    int depth;
    std::cin >> depth;
    int num_moves = game.perft(depth);
    std::cout << "At a depth of " << depth << ", " << num_moves << " different leaf nodes were counted\n";//*/
    return 0;
}