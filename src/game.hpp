#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"

class Game {
    private:
        Board board;
        bool turn, white_queenside, white_kingside, black_queenside, black_kingside;

    public:
        Game();
        void print_game();
};

#endif
