#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game {
    private:
        Board board;
        bool turn, white_queenside, white_kingside, black_queenside, black_kingside;

    public:
        Game();
        void print_game();
};

#endif
